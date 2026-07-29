using Bonsai.Harp;
using System.Threading;
using System.Threading.Tasks;

namespace Harp.FlyPAD
{
    /// <inheritdoc/>
    public partial class Device
    {
        /// <summary>
        /// Initializes a new instance of the asynchronous API to configure and interface
        /// with FlyPAD devices on the specified serial port.
        /// </summary>
        /// <param name="portName">
        /// The name of the serial port used to communicate with the Harp device.
        /// </param>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous initialization operation. The value of
        /// the <see cref="Task{TResult}.Result"/> parameter contains a new instance of
        /// the <see cref="AsyncDevice"/> class.
        /// </returns>
        public static async Task<AsyncDevice> CreateAsync(string portName, CancellationToken cancellationToken = default)
        {
            var device = new AsyncDevice(portName);
            var whoAmI = await device.ReadWhoAmIAsync(cancellationToken);
            if (whoAmI != Device.WhoAmI)
            {
                var errorMessage = string.Format(
                    "The device ID {1} on {0} was unexpected. Check whether a FlyPAD device is connected to the specified serial port.",
                    portName, whoAmI);
                throw new HarpException(errorMessage);
            }

            return device;
        }
    }

    /// <summary>
    /// Represents an asynchronous API to configure and interface with FlyPAD devices.
    /// </summary>
    public partial class AsyncDevice : Bonsai.Harp.AsyncDevice
    {
        internal AsyncDevice(string portName)
            : base(portName)
        {
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="EnableAcquisition"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<EnableFlag> ReadEnableAcquisitionAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(EnableAcquisition.Address), cancellationToken);
            return EnableAcquisition.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="EnableAcquisition"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<EnableFlag>> ReadTimestampedEnableAcquisitionAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(EnableAcquisition.Address), cancellationToken);
            return EnableAcquisition.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously writes a value to the <see cref="EnableAcquisition"/> register.
        /// </summary>
        /// <param name="value">The value to write in the register.</param>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>The task object representing the asynchronous write operation.</returns>
        public async Task WriteEnableAcquisitionAsync(EnableFlag value, CancellationToken cancellationToken = default)
        {
            var request = EnableAcquisition.FromPayload(MessageType.Write, value);
            await CommandAsync(request, cancellationToken);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="CapacitanceValues"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<ushort[]> ReadCapacitanceValuesAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadUInt16(CapacitanceValues.Address), cancellationToken);
            return CapacitanceValues.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="CapacitanceValues"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<ushort[]>> ReadTimestampedCapacitanceValuesAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadUInt16(CapacitanceValues.Address), cancellationToken);
            return CapacitanceValues.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="DI0State"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<DigitalState> ReadDI0StateAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DI0State.Address), cancellationToken);
            return DI0State.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="DI0State"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<DigitalState>> ReadTimestampedDI0StateAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DI0State.Address), cancellationToken);
            return DI0State.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="DI1State"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<DigitalState> ReadDI1StateAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DI1State.Address), cancellationToken);
            return DI1State.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="DI1State"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<DigitalState>> ReadTimestampedDI1StateAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DI1State.Address), cancellationToken);
            return DI1State.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="DigitalOutputSet"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<DigitalOutputs> ReadDigitalOutputSetAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputSet.Address), cancellationToken);
            return DigitalOutputSet.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="DigitalOutputSet"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<DigitalOutputs>> ReadTimestampedDigitalOutputSetAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputSet.Address), cancellationToken);
            return DigitalOutputSet.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously writes a value to the <see cref="DigitalOutputSet"/> register.
        /// </summary>
        /// <param name="value">The value to write in the register.</param>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>The task object representing the asynchronous write operation.</returns>
        public async Task WriteDigitalOutputSetAsync(DigitalOutputs value, CancellationToken cancellationToken = default)
        {
            var request = DigitalOutputSet.FromPayload(MessageType.Write, value);
            await CommandAsync(request, cancellationToken);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="DigitalOutputClear"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<DigitalOutputs> ReadDigitalOutputClearAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputClear.Address), cancellationToken);
            return DigitalOutputClear.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="DigitalOutputClear"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<DigitalOutputs>> ReadTimestampedDigitalOutputClearAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputClear.Address), cancellationToken);
            return DigitalOutputClear.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously writes a value to the <see cref="DigitalOutputClear"/> register.
        /// </summary>
        /// <param name="value">The value to write in the register.</param>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>The task object representing the asynchronous write operation.</returns>
        public async Task WriteDigitalOutputClearAsync(DigitalOutputs value, CancellationToken cancellationToken = default)
        {
            var request = DigitalOutputClear.FromPayload(MessageType.Write, value);
            await CommandAsync(request, cancellationToken);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="DigitalOutputToggle"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<DigitalOutputs> ReadDigitalOutputToggleAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputToggle.Address), cancellationToken);
            return DigitalOutputToggle.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="DigitalOutputToggle"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<DigitalOutputs>> ReadTimestampedDigitalOutputToggleAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputToggle.Address), cancellationToken);
            return DigitalOutputToggle.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously writes a value to the <see cref="DigitalOutputToggle"/> register.
        /// </summary>
        /// <param name="value">The value to write in the register.</param>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>The task object representing the asynchronous write operation.</returns>
        public async Task WriteDigitalOutputToggleAsync(DigitalOutputs value, CancellationToken cancellationToken = default)
        {
            var request = DigitalOutputToggle.FromPayload(MessageType.Write, value);
            await CommandAsync(request, cancellationToken);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="DigitalOutputState"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<DigitalOutputs> ReadDigitalOutputStateAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputState.Address), cancellationToken);
            return DigitalOutputState.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="DigitalOutputState"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<DigitalOutputs>> ReadTimestampedDigitalOutputStateAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(DigitalOutputState.Address), cancellationToken);
            return DigitalOutputState.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously writes a value to the <see cref="DigitalOutputState"/> register.
        /// </summary>
        /// <param name="value">The value to write in the register.</param>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>The task object representing the asynchronous write operation.</returns>
        public async Task WriteDigitalOutputStateAsync(DigitalOutputs value, CancellationToken cancellationToken = default)
        {
            var request = DigitalOutputState.FromPayload(MessageType.Write, value);
            await CommandAsync(request, cancellationToken);
        }

        /// <summary>
        /// Asynchronously reads the contents of the <see cref="EnableEvents"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the register payload.
        /// </returns>
        public async Task<Events> ReadEnableEventsAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(EnableEvents.Address), cancellationToken);
            return EnableEvents.GetPayload(reply);
        }

        /// <summary>
        /// Asynchronously reads the timestamped contents of the <see cref="EnableEvents"/> register.
        /// </summary>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>
        /// A task that represents the asynchronous read operation. The task result contains
        /// the timestamped register payload.
        /// </returns>
        public async Task<Timestamped<Events>> ReadTimestampedEnableEventsAsync(CancellationToken cancellationToken = default)
        {
            var reply = await CommandAsync(HarpCommand.ReadByte(EnableEvents.Address), cancellationToken);
            return EnableEvents.GetTimestampedPayload(reply);
        }

        /// <summary>
        /// Asynchronously writes a value to the <see cref="EnableEvents"/> register.
        /// </summary>
        /// <param name="value">The value to write in the register.</param>
        /// <param name="cancellationToken">
        /// A <see cref="CancellationToken"/> which can be used to cancel the operation.
        /// </param>
        /// <returns>The task object representing the asynchronous write operation.</returns>
        public async Task WriteEnableEventsAsync(Events value, CancellationToken cancellationToken = default)
        {
            var request = EnableEvents.FromPayload(MessageType.Write, value);
            await CommandAsync(request, cancellationToken);
        }
    }
}
