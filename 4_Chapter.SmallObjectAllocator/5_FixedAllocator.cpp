#include "4_Chunks.h"
#include <vector>

// FixedAllocator knows how to allocate and deallocate blocks of a fixed size but is not limited to a chunk's size. Its capacity is
// limited only by available memory.
// To achieve this, FixedAllocator aggregates a vector of Chunk objects. Whenever an allocation
// request occurs, FixedAllocator looks for a Chunk that can accommodate the request. If all Chunk s
// are filled up, FixedAllocator appends a new Chun

class FixedAllocator{
    public:

    void * Allocate();
    void Deallocate();

    private:
    std::size_t blockSize_; //Fixed Allocator already know the block size
    unsigned char numBlocks_;//Number of blocks
    typedef std::vector<Chunk> Chunks;
    Chunks chunks_; //vector with all available chunks, if no chunk available, a new chunk will be appended to the vector
    Chunk * allocChunk_;
    Chunk * deallocChunk_;
    //To increase performance FixedAllocator does not iterate through chunks_
    //looking for space in each allocation.
    //Instead, it holds a pointer to the last pointer that was used for
    //allocation
};

void * FixedAllocator::Allocate()
{
    if(allocChunk_==0 || allocChunk_->blocksAvailable_==0)
    {
        //No available memory in this chunk
        //Try to find one with avail memory
        
        Chunks::iterator i = chunks_.begin();//Remember Chunks is a typdef
        
        //remember, iterator is a object that points to an element inside a container
        //it has overload some operator so it can behave like a pointer in some ways
        //Also you can unitary increase and you move to the next element

        for(;;++i) {
            if (i==chunks_.end())
            {
                //All filled. We need to append a new Chunk object
                chunks_.reserve(chunks_.size()+1);//reserve is more efficient
                Chunk newChunk;
                newChunk.Init(blockSize_,numBlocks_); //numblocks each Chunk contains
                chunks_.push_back(newChunk);
                //set the pointers to the new avail chunk
                allocChunk_ = &chunks_.back();
                //OJO:back() just returns a reference to the last element. while end() returns a pointer or an iterator to the last element
                deallocChunk_ = &chunks_.back();
                break;
            }
            if (i->blocksAvailable_>0)
            {
                //Found a chunk. In this case there are blocks available within chunk i
                allocChunk_=&*i; //get the object in the iterator with *i, and then get its memory address with &.
                break;
            }
        }
    }
    assert(allocChunk_ !=0);
    assert(allocChunk_->blocksAvailable_>0);
    return allocChunk_->Allocate(blockSize_);

}
// Using this strategy, FixedAllocator satisfies most of the allocations in constant time, with occasional
// slowdowns caused by finding and adding a new block. Some memory allocation trends make this scheme
// work inefficiently; however, they tend not to appear often in practice. Don't forget that every allocator has
// an Achilles' heel.


int main(){}