#ifndef DATAMEMORY_H
#define DATAMEMORY_H

namespace riscv_emulator {

const int CACHE_NUM_ADDRESSES = 4000;
const int CACHE_BITS_PER_ADDRESS = 16;

/*! \brief Class for the data (non-instruction) memory of the system.
*
* This class currently only contains basic array for a cache as well as basic get and set functions.
* Will likely later be updated to include a more realistic cache as well as more realistic buses.
*/
class DataMemory {
    private:
        bool Cache[CACHE_NUM_ADDRESSES][CACHE_BITS_PER_ADDRESS];
    public:
        /*! \brief Sets the cache value at a given address to a given value in a boolean string format.
        *
        */
        void set_cache_val(int address, bool val[CACHE_BITS_PER_ADDRESS]);
        /*! \brief Gets the cache value at a given address. Returns the value as an int. Distinct from copy_cache_val, which copies the value into an array.
        * 
        */
        int get_cache_val(int address);
        /*! \brief Copies the cache value at a given address into a given array. Distinct from get_cache_val, which returns the value as an integer.
        *
        */
       void copy_cache_val(int addres, bool given_array[CACHE_BITS_PER_ADDRESS]);

       DataMemory();

};

} // namespace riscv_emulator

#endif