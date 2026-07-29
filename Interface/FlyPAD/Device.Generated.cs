using Bonsai;
using Bonsai.Harp;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reactive.Linq;
using System.Xml.Serialization;

namespace Harp.FlyPAD
{
    /// <summary>
    /// Generates events and processes commands for the FlyPAD device connected
    /// at the specified serial port.
    /// </summary>
    [Combinator(MethodName = nameof(Generate))]
    [WorkflowElementCategory(ElementCategory.Source)]
    [Description("Generates events and processes commands for the FlyPAD device.")]
    public partial class Device : Bonsai.Harp.Device, INamedElement
    {
        /// <summary>
        /// Represents the unique identity class of the <see cref="FlyPAD"/> device.
        /// This field is constant.
        /// </summary>
        public const int WhoAmI = 1201;

        /// <summary>
        /// Initializes a new instance of the <see cref="Device"/> class.
        /// </summary>
        public Device() : base(WhoAmI) { }

        string INamedElement.Name => nameof(FlyPAD);

        /// <summary>
        /// Gets a read-only mapping from address to register type.
        /// </summary>
        public static new IReadOnlyDictionary<int, Type> RegisterMap { get; } = new Dictionary<int, Type>
            (Bonsai.Harp.Device.RegisterMap.ToDictionary(entry => entry.Key, entry => entry.Value))
        {
            { 32, typeof(EnableAcquisition) },
            { 33, typeof(CapacitanceValues) },
            { 34, typeof(DI0State) },
            { 35, typeof(DI1State) },
            { 36, typeof(DigitalOutputSet) },
            { 37, typeof(DigitalOutputClear) },
            { 38, typeof(DigitalOutputToggle) },
            { 39, typeof(DigitalOutputState) },
            { 40, typeof(EnableEvents) }
        };

        /// <summary>
        /// Gets the contents of the metadata file describing the <see cref="FlyPAD"/>
        /// device registers.
        /// </summary>
        public static readonly string Metadata = GetDeviceMetadata();

        static string GetDeviceMetadata()
        {
            var deviceType = typeof(Device);
            using var metadataStream = deviceType.Assembly.GetManifestResourceStream($"{deviceType.Namespace}.device.yml");
            using var streamReader = new System.IO.StreamReader(metadataStream);
            return streamReader.ReadToEnd();
        }
    }

    /// <summary>
    /// Represents an operator that returns the contents of the metadata file
    /// describing the <see cref="FlyPAD"/> device registers.
    /// </summary>
    [Description("Returns the contents of the metadata file describing the FlyPAD device registers.")]
    public partial class GetDeviceMetadata : Source<string>
    {
        /// <summary>
        /// Returns an observable sequence with the contents of the metadata file
        /// describing the <see cref="FlyPAD"/> device registers.
        /// </summary>
        /// <returns>
        /// A sequence with a single <see cref="string"/> object representing the
        /// contents of the metadata file.
        /// </returns>
        public override IObservable<string> Generate()
        {
            return Observable.Return(Device.Metadata);
        }
    }

    /// <summary>
    /// Represents an operator that groups the sequence of <see cref="FlyPAD"/>" messages by register type.
    /// </summary>
    [Description("Groups the sequence of FlyPAD messages by register type.")]
    public partial class GroupByRegister : Combinator<HarpMessage, IGroupedObservable<Type, HarpMessage>>
    {
        /// <summary>
        /// Groups an observable sequence of <see cref="FlyPAD"/> messages
        /// by register type.
        /// </summary>
        /// <param name="source">The sequence of Harp device messages.</param>
        /// <returns>
        /// A sequence of observable groups, each of which corresponds to a unique
        /// <see cref="FlyPAD"/> register.
        /// </returns>
        public override IObservable<IGroupedObservable<Type, HarpMessage>> Process(IObservable<HarpMessage> source)
        {
            return source.GroupBy(message => Device.RegisterMap[message.Address]);
        }
    }

    /// <summary>
    /// Represents an operator that writes the sequence of <see cref="FlyPAD"/>" messages
    /// to the standard Harp storage format.
    /// </summary>
    [DefaultProperty(nameof(Path))]
    [Description("Writes the sequence of FlyPAD messages to the standard Harp storage format.")]
    public partial class DeviceDataWriter : Sink<HarpMessage>, INamedElement
    {
        const string BinaryExtension = ".bin";
        const string MetadataFileName = "device.yml";
        readonly Bonsai.Harp.MessageWriter writer = new();

        string INamedElement.Name => nameof(FlyPAD) + "DataWriter";

        /// <summary>
        /// Gets or sets the relative or absolute path on which to save the message data.
        /// </summary>
        [Description("The relative or absolute path of the directory on which to save the message data.")]
        [Editor("Bonsai.Design.SaveFileNameEditor, Bonsai.Design", DesignTypes.UITypeEditor)]
        public string Path
        {
            get => System.IO.Path.GetDirectoryName(writer.FileName);
            set => writer.FileName = System.IO.Path.Combine(value, nameof(FlyPAD) + BinaryExtension);
        }

        /// <summary>
        /// Gets or sets a value indicating whether element writing should be buffered. If <see langword="true"/>,
        /// the write commands will be queued in memory as fast as possible and will be processed
        /// by the writer in a different thread. Otherwise, writing will be done in the same
        /// thread in which notifications arrive.
        /// </summary>
        [Description("Indicates whether writing should be buffered.")]
        public bool Buffered
        {
            get => writer.Buffered;
            set => writer.Buffered = value;
        }

        /// <summary>
        /// Gets or sets a value indicating whether to overwrite the output file if it already exists.
        /// </summary>
        [Description("Indicates whether to overwrite the output file if it already exists.")]
        public bool Overwrite
        {
            get => writer.Overwrite;
            set => writer.Overwrite = value;
        }

        /// <summary>
        /// Gets or sets a value specifying how the message filter will use the matching criteria.
        /// </summary>
        [Description("Specifies how the message filter will use the matching criteria.")]
        public FilterType FilterType
        {
            get => writer.FilterType;
            set => writer.FilterType = value;
        }

        /// <summary>
        /// Gets or sets a value specifying the expected message type. If no value is
        /// specified, all messages will be accepted.
        /// </summary>
        [Description("Specifies the expected message type. If no value is specified, all messages will be accepted.")]
        public MessageType? MessageType
        {
            get => writer.MessageType;
            set => writer.MessageType = value;
        }

        private IObservable<TSource> WriteDeviceMetadata<TSource>(IObservable<TSource> source)
        {
            var basePath = Path;
            if (string.IsNullOrEmpty(basePath))
                return source;

            var metadataPath = System.IO.Path.Combine(basePath, MetadataFileName);
            return Observable.Create<TSource>(observer =>
            {
                Bonsai.IO.PathHelper.EnsureDirectory(metadataPath);
                if (System.IO.File.Exists(metadataPath) && !Overwrite)
                {
                    throw new System.IO.IOException(string.Format("The file '{0}' already exists.", metadataPath));
                }

                System.IO.File.WriteAllText(metadataPath, Device.Metadata);
                return source.SubscribeSafe(observer);
            });
        }

        /// <summary>
        /// Writes each Harp message in the sequence to the specified binary file, and the
        /// contents of the device metadata file to a separate text file.
        /// </summary>
        /// <param name="source">The sequence of messages to write to the file.</param>
        /// <returns>
        /// An observable sequence that is identical to the <paramref name="source"/>
        /// sequence but where there is an additional side effect of writing the
        /// messages to a raw binary file, and the contents of the device metadata file
        /// to a separate text file.
        /// </returns>
        public override IObservable<HarpMessage> Process(IObservable<HarpMessage> source)
        {
            return source.Publish(ps => ps.Merge(
                WriteDeviceMetadata(writer.Process(ps.GroupBy(message => message.Address)))
                .IgnoreElements()
                .Cast<HarpMessage>()));
        }

        /// <summary>
        /// Writes each Harp message in the sequence of observable groups to the
        /// corresponding binary file, where the name of each file is generated from
        /// the common group register address. The contents of the device metadata file are
        /// written to a separate text file.
        /// </summary>
        /// <param name="source">
        /// A sequence of observable groups, each of which corresponds to a unique register
        /// address.
        /// </param>
        /// <returns>
        /// An observable sequence that is identical to the <paramref name="source"/>
        /// sequence but where there is an additional side effect of writing the Harp
        /// messages in each group to the corresponding file, and the contents of the device
        /// metadata file to a separate text file.
        /// </returns>
        public IObservable<IGroupedObservable<int, HarpMessage>> Process(IObservable<IGroupedObservable<int, HarpMessage>> source)
        {
            return WriteDeviceMetadata(writer.Process(source));
        }

        /// <summary>
        /// Writes each Harp message in the sequence of observable groups to the
        /// corresponding binary file, where the name of each file is generated from
        /// the common group register name. The contents of the device metadata file are
        /// written to a separate text file.
        /// </summary>
        /// <param name="source">
        /// A sequence of observable groups, each of which corresponds to a unique register
        /// type.
        /// </param>
        /// <returns>
        /// An observable sequence that is identical to the <paramref name="source"/>
        /// sequence but where there is an additional side effect of writing the Harp
        /// messages in each group to the corresponding file, and the contents of the device
        /// metadata file to a separate text file.
        /// </returns>
        public IObservable<IGroupedObservable<Type, HarpMessage>> Process(IObservable<IGroupedObservable<Type, HarpMessage>> source)
        {
            return WriteDeviceMetadata(writer.Process(source));
        }
    }

    /// <summary>
    /// Represents an operator that filters register-specific messages
    /// reported by the <see cref="FlyPAD"/> device.
    /// </summary>
    /// <seealso cref="EnableAcquisition"/>
    /// <seealso cref="CapacitanceValues"/>
    /// <seealso cref="DI0State"/>
    /// <seealso cref="DI1State"/>
    /// <seealso cref="DigitalOutputSet"/>
    /// <seealso cref="DigitalOutputClear"/>
    /// <seealso cref="DigitalOutputToggle"/>
    /// <seealso cref="DigitalOutputState"/>
    /// <seealso cref="EnableEvents"/>
    [XmlInclude(typeof(EnableAcquisition))]
    [XmlInclude(typeof(CapacitanceValues))]
    [XmlInclude(typeof(DI0State))]
    [XmlInclude(typeof(DI1State))]
    [XmlInclude(typeof(DigitalOutputSet))]
    [XmlInclude(typeof(DigitalOutputClear))]
    [XmlInclude(typeof(DigitalOutputToggle))]
    [XmlInclude(typeof(DigitalOutputState))]
    [XmlInclude(typeof(EnableEvents))]
    [Description("Filters register-specific messages reported by the FlyPAD device.")]
    public class FilterRegister : FilterRegisterBuilder, INamedElement
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FilterRegister"/> class.
        /// </summary>
        public FilterRegister()
        {
            Register = new EnableAcquisition();
        }

        string INamedElement.Name
        {
            get => $"{nameof(FlyPAD)}.{GetElementDisplayName(Register)}";
        }
    }

    /// <summary>
    /// Represents an operator which filters and selects specific messages
    /// reported by the FlyPAD device.
    /// </summary>
    /// <seealso cref="EnableAcquisition"/>
    /// <seealso cref="CapacitanceValues"/>
    /// <seealso cref="DI0State"/>
    /// <seealso cref="DI1State"/>
    /// <seealso cref="DigitalOutputSet"/>
    /// <seealso cref="DigitalOutputClear"/>
    /// <seealso cref="DigitalOutputToggle"/>
    /// <seealso cref="DigitalOutputState"/>
    /// <seealso cref="EnableEvents"/>
    [XmlInclude(typeof(EnableAcquisition))]
    [XmlInclude(typeof(CapacitanceValues))]
    [XmlInclude(typeof(DI0State))]
    [XmlInclude(typeof(DI1State))]
    [XmlInclude(typeof(DigitalOutputSet))]
    [XmlInclude(typeof(DigitalOutputClear))]
    [XmlInclude(typeof(DigitalOutputToggle))]
    [XmlInclude(typeof(DigitalOutputState))]
    [XmlInclude(typeof(EnableEvents))]
    [XmlInclude(typeof(TimestampedEnableAcquisition))]
    [XmlInclude(typeof(TimestampedCapacitanceValues))]
    [XmlInclude(typeof(TimestampedDI0State))]
    [XmlInclude(typeof(TimestampedDI1State))]
    [XmlInclude(typeof(TimestampedDigitalOutputSet))]
    [XmlInclude(typeof(TimestampedDigitalOutputClear))]
    [XmlInclude(typeof(TimestampedDigitalOutputToggle))]
    [XmlInclude(typeof(TimestampedDigitalOutputState))]
    [XmlInclude(typeof(TimestampedEnableEvents))]
    [Description("Filters and selects specific messages reported by the FlyPAD device.")]
    public partial class Parse : ParseBuilder, INamedElement
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="Parse"/> class.
        /// </summary>
        public Parse()
        {
            Register = new EnableAcquisition();
        }

        string INamedElement.Name => $"{nameof(FlyPAD)}.{GetElementDisplayName(Register)}";
    }

    /// <summary>
    /// Represents an operator which formats a sequence of values as specific
    /// FlyPAD register messages.
    /// </summary>
    /// <seealso cref="EnableAcquisition"/>
    /// <seealso cref="CapacitanceValues"/>
    /// <seealso cref="DI0State"/>
    /// <seealso cref="DI1State"/>
    /// <seealso cref="DigitalOutputSet"/>
    /// <seealso cref="DigitalOutputClear"/>
    /// <seealso cref="DigitalOutputToggle"/>
    /// <seealso cref="DigitalOutputState"/>
    /// <seealso cref="EnableEvents"/>
    [XmlInclude(typeof(EnableAcquisition))]
    [XmlInclude(typeof(CapacitanceValues))]
    [XmlInclude(typeof(DI0State))]
    [XmlInclude(typeof(DI1State))]
    [XmlInclude(typeof(DigitalOutputSet))]
    [XmlInclude(typeof(DigitalOutputClear))]
    [XmlInclude(typeof(DigitalOutputToggle))]
    [XmlInclude(typeof(DigitalOutputState))]
    [XmlInclude(typeof(EnableEvents))]
    [Description("Formats a sequence of values as specific FlyPAD register messages.")]
    public partial class Format : FormatBuilder, INamedElement
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="Format"/> class.
        /// </summary>
        public Format()
        {
            Register = new EnableAcquisition();
        }

        string INamedElement.Name => $"{nameof(FlyPAD)}.{GetElementDisplayName(Register)}";
    }

    /// <summary>
    /// Represents a register that starts or stops the data acquisition in all channels.
    /// </summary>
    [Description("Starts or stops the data acquisition in all channels.")]
    public partial class EnableAcquisition
    {
        /// <summary>
        /// Represents the address of the <see cref="EnableAcquisition"/> register. This field is constant.
        /// </summary>
        public const int Address = 32;

        /// <summary>
        /// Represents the payload type of the <see cref="EnableAcquisition"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="EnableAcquisition"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="EnableAcquisition"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static EnableFlag GetPayload(HarpMessage message)
        {
            return (EnableFlag)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="EnableAcquisition"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<EnableFlag> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((EnableFlag)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="EnableAcquisition"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="EnableAcquisition"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, EnableFlag value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="EnableAcquisition"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="EnableAcquisition"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, EnableFlag value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// EnableAcquisition register.
    /// </summary>
    /// <seealso cref="EnableAcquisition"/>
    [Description("Filters and selects timestamped messages from the EnableAcquisition register.")]
    public partial class TimestampedEnableAcquisition
    {
        /// <summary>
        /// Represents the address of the <see cref="EnableAcquisition"/> register. This field is constant.
        /// </summary>
        public const int Address = EnableAcquisition.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="EnableAcquisition"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<EnableFlag> GetPayload(HarpMessage message)
        {
            return EnableAcquisition.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that value of ADC capacitance values for each channel (2 values per channel).
    /// </summary>
    [Description("Value of ADC capacitance values for each channel (2 values per channel).")]
    public partial class CapacitanceValues
    {
        /// <summary>
        /// Represents the address of the <see cref="CapacitanceValues"/> register. This field is constant.
        /// </summary>
        public const int Address = 33;

        /// <summary>
        /// Represents the payload type of the <see cref="CapacitanceValues"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U16;

        /// <summary>
        /// Represents the length of the <see cref="CapacitanceValues"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 64;

        /// <summary>
        /// Returns the payload data for <see cref="CapacitanceValues"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static ushort[] GetPayload(HarpMessage message)
        {
            return message.GetPayloadArray<ushort>();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="CapacitanceValues"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<ushort[]> GetTimestampedPayload(HarpMessage message)
        {
            return message.GetTimestampedPayloadArray<ushort>();
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="CapacitanceValues"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="CapacitanceValues"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, ushort[] value)
        {
            return HarpMessage.FromUInt16(Address, messageType, value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="CapacitanceValues"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="CapacitanceValues"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, ushort[] value)
        {
            return HarpMessage.FromUInt16(Address, timestamp, messageType, value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// CapacitanceValues register.
    /// </summary>
    /// <seealso cref="CapacitanceValues"/>
    [Description("Filters and selects timestamped messages from the CapacitanceValues register.")]
    public partial class TimestampedCapacitanceValues
    {
        /// <summary>
        /// Represents the address of the <see cref="CapacitanceValues"/> register. This field is constant.
        /// </summary>
        public const int Address = CapacitanceValues.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="CapacitanceValues"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<ushort[]> GetPayload(HarpMessage message)
        {
            return CapacitanceValues.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that state of the digital input pin 0.
    /// </summary>
    [Description("State of the digital input pin 0.")]
    public partial class DI0State
    {
        /// <summary>
        /// Represents the address of the <see cref="DI0State"/> register. This field is constant.
        /// </summary>
        public const int Address = 34;

        /// <summary>
        /// Represents the payload type of the <see cref="DI0State"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="DI0State"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="DI0State"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static DigitalState GetPayload(HarpMessage message)
        {
            return (DigitalState)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="DI0State"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalState> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((DigitalState)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="DI0State"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DI0State"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, DigitalState value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="DI0State"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DI0State"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, DigitalState value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// DI0State register.
    /// </summary>
    /// <seealso cref="DI0State"/>
    [Description("Filters and selects timestamped messages from the DI0State register.")]
    public partial class TimestampedDI0State
    {
        /// <summary>
        /// Represents the address of the <see cref="DI0State"/> register. This field is constant.
        /// </summary>
        public const int Address = DI0State.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="DI0State"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalState> GetPayload(HarpMessage message)
        {
            return DI0State.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that state of the digital input pin 1.
    /// </summary>
    [Description("State of the digital input pin 1.")]
    public partial class DI1State
    {
        /// <summary>
        /// Represents the address of the <see cref="DI1State"/> register. This field is constant.
        /// </summary>
        public const int Address = 35;

        /// <summary>
        /// Represents the payload type of the <see cref="DI1State"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="DI1State"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="DI1State"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static DigitalState GetPayload(HarpMessage message)
        {
            return (DigitalState)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="DI1State"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalState> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((DigitalState)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="DI1State"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DI1State"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, DigitalState value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="DI1State"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DI1State"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, DigitalState value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// DI1State register.
    /// </summary>
    /// <seealso cref="DI1State"/>
    [Description("Filters and selects timestamped messages from the DI1State register.")]
    public partial class TimestampedDI1State
    {
        /// <summary>
        /// Represents the address of the <see cref="DI1State"/> register. This field is constant.
        /// </summary>
        public const int Address = DI1State.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="DI1State"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalState> GetPayload(HarpMessage message)
        {
            return DI1State.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that set the specified digital output lines.
    /// </summary>
    [Description("Set the specified digital output lines.")]
    public partial class DigitalOutputSet
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputSet"/> register. This field is constant.
        /// </summary>
        public const int Address = 36;

        /// <summary>
        /// Represents the payload type of the <see cref="DigitalOutputSet"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="DigitalOutputSet"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="DigitalOutputSet"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static DigitalOutputs GetPayload(HarpMessage message)
        {
            return (DigitalOutputs)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="DigitalOutputSet"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((DigitalOutputs)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="DigitalOutputSet"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputSet"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="DigitalOutputSet"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputSet"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// DigitalOutputSet register.
    /// </summary>
    /// <seealso cref="DigitalOutputSet"/>
    [Description("Filters and selects timestamped messages from the DigitalOutputSet register.")]
    public partial class TimestampedDigitalOutputSet
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputSet"/> register. This field is constant.
        /// </summary>
        public const int Address = DigitalOutputSet.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="DigitalOutputSet"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetPayload(HarpMessage message)
        {
            return DigitalOutputSet.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that clears the specified digital output lines.
    /// </summary>
    [Description("Clears the specified digital output lines.")]
    public partial class DigitalOutputClear
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputClear"/> register. This field is constant.
        /// </summary>
        public const int Address = 37;

        /// <summary>
        /// Represents the payload type of the <see cref="DigitalOutputClear"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="DigitalOutputClear"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="DigitalOutputClear"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static DigitalOutputs GetPayload(HarpMessage message)
        {
            return (DigitalOutputs)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="DigitalOutputClear"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((DigitalOutputs)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="DigitalOutputClear"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputClear"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="DigitalOutputClear"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputClear"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// DigitalOutputClear register.
    /// </summary>
    /// <seealso cref="DigitalOutputClear"/>
    [Description("Filters and selects timestamped messages from the DigitalOutputClear register.")]
    public partial class TimestampedDigitalOutputClear
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputClear"/> register. This field is constant.
        /// </summary>
        public const int Address = DigitalOutputClear.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="DigitalOutputClear"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetPayload(HarpMessage message)
        {
            return DigitalOutputClear.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that toggles the specified digital output lines.
    /// </summary>
    [Description("Toggles the specified digital output lines.")]
    public partial class DigitalOutputToggle
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputToggle"/> register. This field is constant.
        /// </summary>
        public const int Address = 38;

        /// <summary>
        /// Represents the payload type of the <see cref="DigitalOutputToggle"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="DigitalOutputToggle"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="DigitalOutputToggle"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static DigitalOutputs GetPayload(HarpMessage message)
        {
            return (DigitalOutputs)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="DigitalOutputToggle"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((DigitalOutputs)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="DigitalOutputToggle"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputToggle"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="DigitalOutputToggle"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputToggle"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// DigitalOutputToggle register.
    /// </summary>
    /// <seealso cref="DigitalOutputToggle"/>
    [Description("Filters and selects timestamped messages from the DigitalOutputToggle register.")]
    public partial class TimestampedDigitalOutputToggle
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputToggle"/> register. This field is constant.
        /// </summary>
        public const int Address = DigitalOutputToggle.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="DigitalOutputToggle"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetPayload(HarpMessage message)
        {
            return DigitalOutputToggle.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that write the state of all digital output lines.
    /// </summary>
    [Description("Write the state of all digital output lines.")]
    public partial class DigitalOutputState
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputState"/> register. This field is constant.
        /// </summary>
        public const int Address = 39;

        /// <summary>
        /// Represents the payload type of the <see cref="DigitalOutputState"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="DigitalOutputState"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="DigitalOutputState"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static DigitalOutputs GetPayload(HarpMessage message)
        {
            return (DigitalOutputs)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="DigitalOutputState"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((DigitalOutputs)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="DigitalOutputState"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputState"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="DigitalOutputState"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="DigitalOutputState"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, DigitalOutputs value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// DigitalOutputState register.
    /// </summary>
    /// <seealso cref="DigitalOutputState"/>
    [Description("Filters and selects timestamped messages from the DigitalOutputState register.")]
    public partial class TimestampedDigitalOutputState
    {
        /// <summary>
        /// Represents the address of the <see cref="DigitalOutputState"/> register. This field is constant.
        /// </summary>
        public const int Address = DigitalOutputState.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="DigitalOutputState"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<DigitalOutputs> GetPayload(HarpMessage message)
        {
            return DigitalOutputState.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents a register that specifies the active events in the device.
    /// </summary>
    [Description("Specifies the active events in the device.")]
    public partial class EnableEvents
    {
        /// <summary>
        /// Represents the address of the <see cref="EnableEvents"/> register. This field is constant.
        /// </summary>
        public const int Address = 40;

        /// <summary>
        /// Represents the payload type of the <see cref="EnableEvents"/> register. This field is constant.
        /// </summary>
        public const PayloadType RegisterType = PayloadType.U8;

        /// <summary>
        /// Represents the length of the <see cref="EnableEvents"/> register. This field is constant.
        /// </summary>
        public const int RegisterLength = 1;

        /// <summary>
        /// Returns the payload data for <see cref="EnableEvents"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the message payload.</returns>
        public static Events GetPayload(HarpMessage message)
        {
            return (Events)message.GetPayloadByte();
        }

        /// <summary>
        /// Returns the timestamped payload data for <see cref="EnableEvents"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<Events> GetTimestampedPayload(HarpMessage message)
        {
            var payload = message.GetTimestampedPayloadByte();
            return Timestamped.Create((Events)payload.Value, payload.Seconds);
        }

        /// <summary>
        /// Returns a Harp message for the <see cref="EnableEvents"/> register.
        /// </summary>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="EnableEvents"/> register
        /// with the specified message type and payload.
        /// </returns>
        public static HarpMessage FromPayload(MessageType messageType, Events value)
        {
            return HarpMessage.FromByte(Address, messageType, (byte)value);
        }

        /// <summary>
        /// Returns a timestamped Harp message for the <see cref="EnableEvents"/>
        /// register.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">The type of the Harp message.</param>
        /// <param name="value">The value to be stored in the message payload.</param>
        /// <returns>
        /// A <see cref="HarpMessage"/> object for the <see cref="EnableEvents"/> register
        /// with the specified message type, timestamp, and payload.
        /// </returns>
        public static HarpMessage FromPayload(double timestamp, MessageType messageType, Events value)
        {
            return HarpMessage.FromByte(Address, timestamp, messageType, (byte)value);
        }
    }

    /// <summary>
    /// Provides methods for manipulating timestamped messages from the
    /// EnableEvents register.
    /// </summary>
    /// <seealso cref="EnableEvents"/>
    [Description("Filters and selects timestamped messages from the EnableEvents register.")]
    public partial class TimestampedEnableEvents
    {
        /// <summary>
        /// Represents the address of the <see cref="EnableEvents"/> register. This field is constant.
        /// </summary>
        public const int Address = EnableEvents.Address;

        /// <summary>
        /// Returns timestamped payload data for <see cref="EnableEvents"/> register messages.
        /// </summary>
        /// <param name="message">A <see cref="HarpMessage"/> object representing the register message.</param>
        /// <returns>A value representing the timestamped message payload.</returns>
        public static Timestamped<Events> GetPayload(HarpMessage message)
        {
            return EnableEvents.GetTimestampedPayload(message);
        }
    }

    /// <summary>
    /// Represents an operator which creates standard message payloads for the
    /// FlyPAD device.
    /// </summary>
    /// <seealso cref="CreateEnableAcquisitionPayload"/>
    /// <seealso cref="CreateCapacitanceValuesPayload"/>
    /// <seealso cref="CreateDI0StatePayload"/>
    /// <seealso cref="CreateDI1StatePayload"/>
    /// <seealso cref="CreateDigitalOutputSetPayload"/>
    /// <seealso cref="CreateDigitalOutputClearPayload"/>
    /// <seealso cref="CreateDigitalOutputTogglePayload"/>
    /// <seealso cref="CreateDigitalOutputStatePayload"/>
    /// <seealso cref="CreateEnableEventsPayload"/>
    [XmlInclude(typeof(CreateEnableAcquisitionPayload))]
    [XmlInclude(typeof(CreateCapacitanceValuesPayload))]
    [XmlInclude(typeof(CreateDI0StatePayload))]
    [XmlInclude(typeof(CreateDI1StatePayload))]
    [XmlInclude(typeof(CreateDigitalOutputSetPayload))]
    [XmlInclude(typeof(CreateDigitalOutputClearPayload))]
    [XmlInclude(typeof(CreateDigitalOutputTogglePayload))]
    [XmlInclude(typeof(CreateDigitalOutputStatePayload))]
    [XmlInclude(typeof(CreateEnableEventsPayload))]
    [XmlInclude(typeof(CreateTimestampedEnableAcquisitionPayload))]
    [XmlInclude(typeof(CreateTimestampedCapacitanceValuesPayload))]
    [XmlInclude(typeof(CreateTimestampedDI0StatePayload))]
    [XmlInclude(typeof(CreateTimestampedDI1StatePayload))]
    [XmlInclude(typeof(CreateTimestampedDigitalOutputSetPayload))]
    [XmlInclude(typeof(CreateTimestampedDigitalOutputClearPayload))]
    [XmlInclude(typeof(CreateTimestampedDigitalOutputTogglePayload))]
    [XmlInclude(typeof(CreateTimestampedDigitalOutputStatePayload))]
    [XmlInclude(typeof(CreateTimestampedEnableEventsPayload))]
    [Description("Creates standard message payloads for the FlyPAD device.")]
    public partial class CreateMessage : CreateMessageBuilder, INamedElement
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CreateMessage"/> class.
        /// </summary>
        public CreateMessage()
        {
            Payload = new CreateEnableAcquisitionPayload();
        }

        string INamedElement.Name => $"{nameof(FlyPAD)}.{GetElementDisplayName(Payload)}";
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that starts or stops the data acquisition in all channels.
    /// </summary>
    [DisplayName("EnableAcquisitionPayload")]
    [Description("Creates a message payload that starts or stops the data acquisition in all channels.")]
    public partial class CreateEnableAcquisitionPayload
    {
        /// <summary>
        /// Gets or sets the value that starts or stops the data acquisition in all channels.
        /// </summary>
        [Description("The value that starts or stops the data acquisition in all channels.")]
        public EnableFlag EnableAcquisition { get; set; }

        /// <summary>
        /// Creates a message payload for the EnableAcquisition register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public EnableFlag GetPayload()
        {
            return EnableAcquisition;
        }

        /// <summary>
        /// Creates a message that starts or stops the data acquisition in all channels.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the EnableAcquisition register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.EnableAcquisition.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that starts or stops the data acquisition in all channels.
    /// </summary>
    [DisplayName("TimestampedEnableAcquisitionPayload")]
    [Description("Creates a timestamped message payload that starts or stops the data acquisition in all channels.")]
    public partial class CreateTimestampedEnableAcquisitionPayload : CreateEnableAcquisitionPayload
    {
        /// <summary>
        /// Creates a timestamped message that starts or stops the data acquisition in all channels.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the EnableAcquisition register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.EnableAcquisition.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that value of ADC capacitance values for each channel (2 values per channel).
    /// </summary>
    [DisplayName("CapacitanceValuesPayload")]
    [Description("Creates a message payload that value of ADC capacitance values for each channel (2 values per channel).")]
    public partial class CreateCapacitanceValuesPayload
    {
        /// <summary>
        /// Gets or sets the value that value of ADC capacitance values for each channel (2 values per channel).
        /// </summary>
        [Description("The value that value of ADC capacitance values for each channel (2 values per channel).")]
        public ushort[] CapacitanceValues { get; set; }

        /// <summary>
        /// Creates a message payload for the CapacitanceValues register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public ushort[] GetPayload()
        {
            return CapacitanceValues;
        }

        /// <summary>
        /// Creates a message that value of ADC capacitance values for each channel (2 values per channel).
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the CapacitanceValues register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.CapacitanceValues.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that value of ADC capacitance values for each channel (2 values per channel).
    /// </summary>
    [DisplayName("TimestampedCapacitanceValuesPayload")]
    [Description("Creates a timestamped message payload that value of ADC capacitance values for each channel (2 values per channel).")]
    public partial class CreateTimestampedCapacitanceValuesPayload : CreateCapacitanceValuesPayload
    {
        /// <summary>
        /// Creates a timestamped message that value of ADC capacitance values for each channel (2 values per channel).
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the CapacitanceValues register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.CapacitanceValues.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that state of the digital input pin 0.
    /// </summary>
    [DisplayName("DI0StatePayload")]
    [Description("Creates a message payload that state of the digital input pin 0.")]
    public partial class CreateDI0StatePayload
    {
        /// <summary>
        /// Gets or sets the value that state of the digital input pin 0.
        /// </summary>
        [Description("The value that state of the digital input pin 0.")]
        public DigitalState DI0State { get; set; }

        /// <summary>
        /// Creates a message payload for the DI0State register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public DigitalState GetPayload()
        {
            return DI0State;
        }

        /// <summary>
        /// Creates a message that state of the digital input pin 0.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the DI0State register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.DI0State.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that state of the digital input pin 0.
    /// </summary>
    [DisplayName("TimestampedDI0StatePayload")]
    [Description("Creates a timestamped message payload that state of the digital input pin 0.")]
    public partial class CreateTimestampedDI0StatePayload : CreateDI0StatePayload
    {
        /// <summary>
        /// Creates a timestamped message that state of the digital input pin 0.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the DI0State register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.DI0State.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that state of the digital input pin 1.
    /// </summary>
    [DisplayName("DI1StatePayload")]
    [Description("Creates a message payload that state of the digital input pin 1.")]
    public partial class CreateDI1StatePayload
    {
        /// <summary>
        /// Gets or sets the value that state of the digital input pin 1.
        /// </summary>
        [Description("The value that state of the digital input pin 1.")]
        public DigitalState DI1State { get; set; }

        /// <summary>
        /// Creates a message payload for the DI1State register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public DigitalState GetPayload()
        {
            return DI1State;
        }

        /// <summary>
        /// Creates a message that state of the digital input pin 1.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the DI1State register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.DI1State.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that state of the digital input pin 1.
    /// </summary>
    [DisplayName("TimestampedDI1StatePayload")]
    [Description("Creates a timestamped message payload that state of the digital input pin 1.")]
    public partial class CreateTimestampedDI1StatePayload : CreateDI1StatePayload
    {
        /// <summary>
        /// Creates a timestamped message that state of the digital input pin 1.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the DI1State register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.DI1State.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that set the specified digital output lines.
    /// </summary>
    [DisplayName("DigitalOutputSetPayload")]
    [Description("Creates a message payload that set the specified digital output lines.")]
    public partial class CreateDigitalOutputSetPayload
    {
        /// <summary>
        /// Gets or sets the value that set the specified digital output lines.
        /// </summary>
        [Description("The value that set the specified digital output lines.")]
        public DigitalOutputs DigitalOutputSet { get; set; }

        /// <summary>
        /// Creates a message payload for the DigitalOutputSet register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public DigitalOutputs GetPayload()
        {
            return DigitalOutputSet;
        }

        /// <summary>
        /// Creates a message that set the specified digital output lines.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the DigitalOutputSet register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputSet.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that set the specified digital output lines.
    /// </summary>
    [DisplayName("TimestampedDigitalOutputSetPayload")]
    [Description("Creates a timestamped message payload that set the specified digital output lines.")]
    public partial class CreateTimestampedDigitalOutputSetPayload : CreateDigitalOutputSetPayload
    {
        /// <summary>
        /// Creates a timestamped message that set the specified digital output lines.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the DigitalOutputSet register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputSet.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that clears the specified digital output lines.
    /// </summary>
    [DisplayName("DigitalOutputClearPayload")]
    [Description("Creates a message payload that clears the specified digital output lines.")]
    public partial class CreateDigitalOutputClearPayload
    {
        /// <summary>
        /// Gets or sets the value that clears the specified digital output lines.
        /// </summary>
        [Description("The value that clears the specified digital output lines.")]
        public DigitalOutputs DigitalOutputClear { get; set; }

        /// <summary>
        /// Creates a message payload for the DigitalOutputClear register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public DigitalOutputs GetPayload()
        {
            return DigitalOutputClear;
        }

        /// <summary>
        /// Creates a message that clears the specified digital output lines.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the DigitalOutputClear register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputClear.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that clears the specified digital output lines.
    /// </summary>
    [DisplayName("TimestampedDigitalOutputClearPayload")]
    [Description("Creates a timestamped message payload that clears the specified digital output lines.")]
    public partial class CreateTimestampedDigitalOutputClearPayload : CreateDigitalOutputClearPayload
    {
        /// <summary>
        /// Creates a timestamped message that clears the specified digital output lines.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the DigitalOutputClear register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputClear.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that toggles the specified digital output lines.
    /// </summary>
    [DisplayName("DigitalOutputTogglePayload")]
    [Description("Creates a message payload that toggles the specified digital output lines.")]
    public partial class CreateDigitalOutputTogglePayload
    {
        /// <summary>
        /// Gets or sets the value that toggles the specified digital output lines.
        /// </summary>
        [Description("The value that toggles the specified digital output lines.")]
        public DigitalOutputs DigitalOutputToggle { get; set; }

        /// <summary>
        /// Creates a message payload for the DigitalOutputToggle register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public DigitalOutputs GetPayload()
        {
            return DigitalOutputToggle;
        }

        /// <summary>
        /// Creates a message that toggles the specified digital output lines.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the DigitalOutputToggle register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputToggle.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that toggles the specified digital output lines.
    /// </summary>
    [DisplayName("TimestampedDigitalOutputTogglePayload")]
    [Description("Creates a timestamped message payload that toggles the specified digital output lines.")]
    public partial class CreateTimestampedDigitalOutputTogglePayload : CreateDigitalOutputTogglePayload
    {
        /// <summary>
        /// Creates a timestamped message that toggles the specified digital output lines.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the DigitalOutputToggle register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputToggle.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that write the state of all digital output lines.
    /// </summary>
    [DisplayName("DigitalOutputStatePayload")]
    [Description("Creates a message payload that write the state of all digital output lines.")]
    public partial class CreateDigitalOutputStatePayload
    {
        /// <summary>
        /// Gets or sets the value that write the state of all digital output lines.
        /// </summary>
        [Description("The value that write the state of all digital output lines.")]
        public DigitalOutputs DigitalOutputState { get; set; }

        /// <summary>
        /// Creates a message payload for the DigitalOutputState register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public DigitalOutputs GetPayload()
        {
            return DigitalOutputState;
        }

        /// <summary>
        /// Creates a message that write the state of all digital output lines.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the DigitalOutputState register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputState.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that write the state of all digital output lines.
    /// </summary>
    [DisplayName("TimestampedDigitalOutputStatePayload")]
    [Description("Creates a timestamped message payload that write the state of all digital output lines.")]
    public partial class CreateTimestampedDigitalOutputStatePayload : CreateDigitalOutputStatePayload
    {
        /// <summary>
        /// Creates a timestamped message that write the state of all digital output lines.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the DigitalOutputState register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.DigitalOutputState.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a message payload
    /// that specifies the active events in the device.
    /// </summary>
    [DisplayName("EnableEventsPayload")]
    [Description("Creates a message payload that specifies the active events in the device.")]
    public partial class CreateEnableEventsPayload
    {
        /// <summary>
        /// Gets or sets the value that specifies the active events in the device.
        /// </summary>
        [Description("The value that specifies the active events in the device.")]
        public Events EnableEvents { get; set; }

        /// <summary>
        /// Creates a message payload for the EnableEvents register.
        /// </summary>
        /// <returns>The created message payload value.</returns>
        public Events GetPayload()
        {
            return EnableEvents;
        }

        /// <summary>
        /// Creates a message that specifies the active events in the device.
        /// </summary>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new message for the EnableEvents register.</returns>
        public HarpMessage GetMessage(MessageType messageType)
        {
            return Harp.FlyPAD.EnableEvents.FromPayload(messageType, GetPayload());
        }
    }

    /// <summary>
    /// Represents an operator that creates a timestamped message payload
    /// that specifies the active events in the device.
    /// </summary>
    [DisplayName("TimestampedEnableEventsPayload")]
    [Description("Creates a timestamped message payload that specifies the active events in the device.")]
    public partial class CreateTimestampedEnableEventsPayload : CreateEnableEventsPayload
    {
        /// <summary>
        /// Creates a timestamped message that specifies the active events in the device.
        /// </summary>
        /// <param name="timestamp">The timestamp of the message payload, in seconds.</param>
        /// <param name="messageType">Specifies the type of the created message.</param>
        /// <returns>A new timestamped message for the EnableEvents register.</returns>
        public HarpMessage GetMessage(double timestamp, MessageType messageType)
        {
            return Harp.FlyPAD.EnableEvents.FromPayload(timestamp, messageType, GetPayload());
        }
    }

    /// <summary>
    /// Specifies the state of the digital outputs.
    /// </summary>
    [Flags]
    public enum DigitalOutputs : byte
    {
        None = 0x0,
        DO0 = 0x1,
        DO1 = 0x2,
        DO2 = 0x4,
        DO3 = 0x8
    }

    /// <summary>
    /// Specifies the events to be sent.
    /// </summary>
    [Flags]
    public enum Events : byte
    {
        None = 0x0,
        DigitalInputs = 0x1
    }

    /// <summary>
    /// The state of a digital pin.
    /// </summary>
    public enum DigitalState : byte
    {
        Low = 0,
        High = 1
    }

    internal static partial class PayloadMarshal
    {
        internal static T[] GetSubArray<T>(T[] array, int offset, int count)
        {
            var result = new T[count];
            Array.Copy(array, offset, result, 0, count);
            return result;
        }

        internal static byte ReadByte(ArraySegment<byte> segment) => segment.Array[segment.Offset];

        internal static sbyte ReadSByte(ArraySegment<byte> segment) => (sbyte)segment.Array[segment.Offset];

        internal static ushort ReadUInt16(ArraySegment<byte> segment) => BitConverter.ToUInt16(segment.Array, segment.Offset);

        internal static short ReadInt16(ArraySegment<byte> segment) => BitConverter.ToInt16(segment.Array, segment.Offset);

        internal static uint ReadUInt32(ArraySegment<byte> segment) => BitConverter.ToUInt32(segment.Array, segment.Offset);

        internal static int ReadInt32(ArraySegment<byte> segment) => BitConverter.ToInt32(segment.Array, segment.Offset);

        internal static ulong ReadUInt64(ArraySegment<byte> segment) => BitConverter.ToUInt64(segment.Array, segment.Offset);

        internal static long ReadInt64(ArraySegment<byte> segment) => BitConverter.ToInt64(segment.Array, segment.Offset);

        internal static float ReadSingle(ArraySegment<byte> segment) => BitConverter.ToSingle(segment.Array, segment.Offset);

        internal static string ReadUtf8String(ArraySegment<byte> segment)
        {
            var count = Array.IndexOf(segment.Array, (byte)0, segment.Offset, segment.Count) - segment.Offset;
            return System.Text.Encoding.UTF8.GetString(segment.Array, segment.Offset, count < 0 ? segment.Count : count);
        }

        internal static void Write(ArraySegment<byte> segment, byte value) => segment.Array[segment.Offset] = value;

        internal static void Write(ArraySegment<byte> segment, sbyte value) => segment.Array[segment.Offset] = (byte)value;

        internal static void Write(ArraySegment<byte> segment, ushort value)
        {
            segment.Array[segment.Offset] = (byte)value;
            segment.Array[segment.Offset + 1] = (byte)(value >> 8);
        }

        internal static void Write(ArraySegment<byte> segment, short value)
        {
            segment.Array[segment.Offset] = (byte)value;
            segment.Array[segment.Offset + 1] = (byte)(value >> 8);
        }

        internal static void Write(ArraySegment<byte> segment, uint value)
        {
            segment.Array[segment.Offset] = (byte)value;
            segment.Array[segment.Offset + 1] = (byte)(value >> 8);
            segment.Array[segment.Offset + 2] = (byte)(value >> 16);
            segment.Array[segment.Offset + 3] = (byte)(value >> 24);
        }

        internal static void Write(ArraySegment<byte> segment, int value)
        {
            segment.Array[segment.Offset] = (byte)value;
            segment.Array[segment.Offset + 1] = (byte)(value >> 8);
            segment.Array[segment.Offset + 2] = (byte)(value >> 16);
            segment.Array[segment.Offset + 3] = (byte)(value >> 24);
        }

        internal static void Write(ArraySegment<byte> segment, ulong value)
        {
            segment.Array[segment.Offset] = (byte)value;
            segment.Array[segment.Offset + 1] = (byte)(value >> 8);
            segment.Array[segment.Offset + 2] = (byte)(value >> 16);
            segment.Array[segment.Offset + 3] = (byte)(value >> 24);
            segment.Array[segment.Offset + 4] = (byte)(value >> 32);
            segment.Array[segment.Offset + 5] = (byte)(value >> 40);
            segment.Array[segment.Offset + 6] = (byte)(value >> 48);
            segment.Array[segment.Offset + 7] = (byte)(value >> 56);
        }

        internal static void Write(ArraySegment<byte> segment, long value)
        {
            segment.Array[segment.Offset] = (byte)value;
            segment.Array[segment.Offset + 1] = (byte)(value >> 8);
            segment.Array[segment.Offset + 2] = (byte)(value >> 16);
            segment.Array[segment.Offset + 3] = (byte)(value >> 24);
            segment.Array[segment.Offset + 4] = (byte)(value >> 32);
            segment.Array[segment.Offset + 5] = (byte)(value >> 40);
            segment.Array[segment.Offset + 6] = (byte)(value >> 48);
            segment.Array[segment.Offset + 7] = (byte)(value >> 56);
        }

        internal static unsafe void Write(ArraySegment<byte> segment, float value) => Write(segment, *(int*)&value);

        internal static unsafe void Write(ArraySegment<byte> segment, string value) =>
            System.Text.Encoding.UTF8.GetBytes(value, 0, Math.Min(value.Length, segment.Count), segment.Array, segment.Offset);

        internal static void Write<T>(ArraySegment<byte> segment, T[] values) where T : unmanaged
        {
            Buffer.BlockCopy(values, 0, segment.Array, segment.Offset, segment.Count);
        }

        internal static void Write<T>(ArraySegment<T> segment, T[] values)
        {
            Array.Copy(values, 0, segment.Array, segment.Offset, segment.Count);
        }
    }
}
