#ifndef IOPERIPHERAL_H
#define IOPERIPHERAL_H

namespace riscv_emulator {

const int PACKET_SIZE = 32;

/*! \brief Class for ioPerhipheral(s). This can be attached to the processor to represent streaming instructions and data to the relevent memories.
*
* The functions for this class are neutral as to whether or not the stream is for instructions or data.
* This means the packet size is set independently of either the instruction size or the data size.
* Rationale: Don't want to duplicate work by creating streams for both instructions and data.
* Furthermore, this peripheral ought to be flexible so the streams aren't locked down to only instructions or data.
*/
class ioPeripheral {
    private:
        bool stream_on = 0;
        bool my_packet[PACKET_SIZE] = { };
        void get_packet_from_file();
    public:
        void begin_stream_from_file();
        void end_stream_from_file();
        void copy_packet();
};

} // namespace riscv_emulator

#endif

