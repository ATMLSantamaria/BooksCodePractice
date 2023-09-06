#include <cstddef>
#include <cassert>
// Each object of type Chunk contains and manages a chunk of memory containing a fixed amount of blocks.
// At construction time, you configure the block size and the number of blocks.
// A Chunk contains logic that allows you to allocate and deallocate memory blocks from that chunk of
// memory. When there are no more blocks available in the chunk, the allocation function returns zero.

// Nothing is private — Chunk is a Plain Old Data (POD) structure

struct Chunk
{
    void Init(std::size_t blockSize,unsigned char blocks);
    void * Allocate(std::size_t blockSize);
    void Deallocate(void *p,std::size_t blockSize);
    unsigned char * pData_; //pData is the memory address of the origin of the Chunk
    unsigned char firstAvailableBlock_, //which holds the index of the first block available in this chunk
                     blocksAvailable_;  //number of blocks available in this chunk
};

// You have to pass a size to Allocate and Deallocate because Chunk does not hold it. 

// This is because the block size is known at a superior level. Chunk would waste space and time if it redundantly kept a
// blockSize_ member. Don't forget we are at the very bottom here—everything matters. Again for
// efficiency reasons, Chunk does not define constructors, destructors, or assignment operator

// Because blocksAvailable_ and
// firstAvailableBlock_ are of type unsigned char , it follows that you cannot have a chunk that
// contains more than 255 blocks (on a machine with 8-bit characters).

// We can store whatever we want in an
// unused block, so we take advantage of this. The first byte of an unused block holds the index of the next
// unused block. Because we hold the first available index in firstAvailableBlock_ , we have a full-
// fledged singly linked list of unused blocks without using any extra memory.

void Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
    pData_ = new unsigned char[blockSize * blocks]; //Allocate enough space for all blocks
    firstAvailableBlock_ = 0; //At initialization chunck is empty
    blocksAvailable_ = blocks; //At initialization the number of blocksAvailable is the total number of blocks
    unsigned char i = 0;
    unsigned char *p = pData_;
    for (;i!=blocks;p+=blockSize)
    {
        *p=++i; 
        //p avanza bloque a bloque comenzando por el bloque 0, i avanza de 1 en 1 comenzando por 1. 
        //Remember -> The first byte of an unused block holds the index of the next unused block
        //En principio todos los bloques estan sin usar, y su primer bit guarda el index del siguiente bloque sin usar
    }
    // This singly linked list melted inside the data structure is an essential goodie. It offers a fast, efficient way
    // of finding available blocks inside a chunk—without any extra cost in size. Allocating and deallocating a
    // block inside a Chunk takes constant time, which is exclusively thanks to the embedded singly linked list.
}
// We use unsigned char(1byte) as the type of the "stealth index." because is 1byte so it allows us the maximum granularity and to avoid run into aligment issues. 
// If for example you use unsigned int (2bytes) and you want to allcoate blocks of size 5bytes the behavious is undefine and you may have issues

// This limit the maximum number of blocks in a chunk. We cannot have more than UCHAR_MAX blocks in a chunk (255 on most systems)


//Allocate 1 block
void * Chunk::Allocate(std::size_t blocksSize){
    if (!blocksAvailable_) return 0; //if blocksAvailable is different than 0, is cast to true, and with the ! became false. So it does not return 0 if there are available blocks
    
    unsigned char * pResult = pData_ + (firstAvailableBlock_*blocksSize); //Give back a pointer to the place where the block was allocated
    // Update firstAvailableBlock_ to point to the next block
    firstAvailableBlock_ = *pResult; //firstAvailableBlock retrieve the index of the next available block
    --blocksAvailable_;
    return pResult;
}

//A chunck object after one allocation:
// firstAvailableBlock = 1; //porque 0 esta ya allocate
// blocksAvailable = 254; //255 -1

void Chunk::Deallocate(void *p,std::size_t blockSize)
{
    assert(p>=pData_); //Assure we are deallocating a block that is within the Chunk. so its memory address is bigger that the memory address pData that point the start of the Chunk
    unsigned char *toRelease = static_cast<unsigned char *>(p);
    // Alligment check
    assert((toRelease-pData_)%blockSize==0);//The released block of memory should be a multiple of blocksize. So we can relese 1 block, 2 blocks... but never a fraction
    *toRelease = firstAvailableBlock_;//the released block now is empty and store the index of the next 1st available block
    //we reassign the firstAvailable block to the released block
    firstAvailableBlock_ = static_cast<unsigned char>((toRelease - pData_) / blockSize);
    // Truncation check
    assert(firstAvailableBlock_ ==(toRelease - pData_) / blockSize);
    //Note to remember: Truncation shortens a decimal-based value such as a float or a double to its integral form int with the extra precision bits after the decimal (from 2-1 in corresponding decimal form) removed
    ++blocksAvailable_;
}
