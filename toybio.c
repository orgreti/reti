int readPage(struct block_device *device, sector_t sector, int size,
     struct page *page)
{
    int ret;
    struct completion event;
    struct bio *bio = bio_alloc(GFP_NOIO, 1);
    bio->bi_bdev = device;
    bio->bi_sector = sector;

    bio_add_page(bio, page, size, 0);
    init_completion(&event);

    bio->bi_private = &event;
    bio->bi_end_io = readComplete;

    submit_bio(READ | REQ_SYNC, bio);
    wait_for_completion(&event);
    ret = test_bit(BIO_UPTODATE, &bio->bi_flags);

    bio_put(bio);
    return ret;
}


void writePage(struct block_device *device,
    sector_t sector, int size, struct page *page)
{
    struct bio *bio = bio_alloc(GFP_NOIO, 1);
    bio->bi_bdev = device;
    bio->bi_sector = sector;

    bio_add_page(bio, page, size, 0);
    bio->bi_end_io = writeComplete;

    submit_bio(WRITE_FLUSH_FUA, bio);
}

void write_sector(char const* path, int sector, int size, char* data)
{
	// Generate block device from path // blk-get-by-path
	// Generate page from data  // 
	// get sector, get page by dividing sector by (2^(12-9))
	// filler functions  // 
	// Compute  nbytes : number of bytes in the payload
	// Generate sector from block
	writePage(device, sector, npage, page);
}

char* read_sector(char const* path, int block, int size)
{
	// Generate block device from path
	// Generate page from  
	// Compute  nbytes : number of bytes in the payload
	// Generate sector from block
	writePage(device, sector, npage, page);
}
