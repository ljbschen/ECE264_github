#include "answer07.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define BIT 8

static int checkValid(ImageHeader * header);
static void printHeader(ImageHeader * header);

// -------------------------------------------------------------- Image_load
Image * Image_load(const char * filename) {
	FILE *fp = NULL;
	size_t read = 0;
    ImageHeader header;
    Image * tmp_im = NULL, * im = NULL;
    size_t n_bytes = 0;
    int err = FALSE;

    //(1) Make sure you can open the file-----------------------------------------
    if(!err) {
    	fp = fopen(filename, "rb");
		if(!fp) {
	    	fprintf(stderr, "Failed to open file '%s'\n", filename);
	    	err = TRUE;
		}
    }

    //(2) Read the header:--------------------------------------------------------
    if(!err) { 
		read = fread(&header, sizeof(ImageHeader), 1, fp);
		//(2.a) Make sure that you can read all the bytes of the header
		if(read != 1) {
	    	fprintf(stderr, "Failed to read header from '%s'\n", filename);
	    	err = TRUE;
		}
    }

    //Check each field in header---------------------------------------------------
    //(2.b) Make sure that the magic_number in the header is correct
    //(2.c) Make sure that neither the width nor height is zero
    //(2.d) Make sure that the comment length is not zero. (Remember, 
    //      it includes the null-byte.)
    if(!err) { 
		if(!checkValid(&header)) {
	    	fprintf(stderr, "Invalid header in '%s'\n", filename);
	   	 err = TRUE;
		}
    }

    //Print the header------------------------------------------------------------
    if(!err) { 
		printHeader(&header);
    }

    //Allocate Image struct--------------------------------------------------------
    if(!err) { 
		tmp_im = malloc(sizeof(Image));			
		//(3) Allocate space for the image, comment, and pixels. Remember
		//    malloc will return NULL if it cannot do its job.
		if(tmp_im == NULL) {
	    	fprintf(stderr, "Failed to allocate im structure\n");
	    	err = TRUE;
		} 
    }

    // Init the Image struct-----------------------------------------------------
    if(!err) {
		tmp_im->width = header.width;
		tmp_im->height = header.height;
		//(4) Read the comment
		//(4.0) Make sure enough space is allocated for comment
		tmp_im->comment = malloc(header.comment_len);
		if(!err && tmp_im->comment == NULL) {
	    	fprintf(stderr, "Failed to allocate %zd bytes for comment\n",
		    	(size_t)header.comment_len);
	    	err = TRUE;
		} 
		//(4.a) Make sure you read the entire comment
		read = fread(tmp_im->comment, sizeof(char), header.comment_len, fp);
		if (!err && read != (size_t)header.comment_len){
			fprintf(stderr, "Failed to read the entire comment\nOnly read %zd chars for comment",
		    	read);
	    	err = TRUE;
		}
		//(4.b) Make sure the comment ends in a null-byte.
		if (!err && tmp_im->comment[header.comment_len - 1] != '\0') {
			fprintf(stderr, "Failed to find null byte on comment");
	    	err = TRUE;
		}

		// Handle image data
		n_bytes = sizeof(uint8_t) * header.width * header.height;
		tmp_im->data = malloc(n_bytes);
		if(!err && tmp_im->data == NULL) {
		    fprintf(stderr, "Failed to allocate %zd bytes for image data\n",
			    n_bytes);
		    err = TRUE;
		}
	}

	// Read pixel data--------------------------------------------------------------------------
	//(5)   Read the pixels
	
    if(!err) { 
    	//size_t bytes_per_row = ((BIT * header.width + 31)/32)*4;
		//n_bytes = bytes_per_row * header.height;
		uint8_t * rawimage = malloc(n_bytes);
		//(5.0) Make sure enough space is allocated for data
		if(rawimage == NULL) {
		    fprintf(stderr, "Could not allocate %zd bytes of image data\n",
			    n_bytes);
		    err = TRUE;
		} 
		else {
			//(5.a) Make sure you read *all* width*height pixels
		    read = fread(rawimage, sizeof(uint8_t), n_bytes, fp);
		    if(n_bytes != read ) {
				fprintf(stderr, "Only read %zd of %zd bytes of image data\n", 
					read, n_bytes);
				err = TRUE;
		    } 
		    else {
		    	//store raw data in tem_im -> data
		    	uint8_t * write_ptr = tmp_im->data;
				uint8_t * read_ptr;
				int row, col; // row and column
				for(row = 0; row < header.height; row++) {
				    read_ptr = &rawimage[row * header.width];
				    for(col = 0; col < header.width; col++) {
						*write_ptr++ = *read_ptr++; 
				    }
				}
				//normolize here
		    	linearNormalization(tmp_im->width, tmp_im->height, tmp_im->data);
		    }
		}
		free(rawimage);
	}

	// We should be at the end of the file now---------------------------------------------------
	//(5.b) Make sure you've reached the end of the file. (i.e., there are
	//      no trailing bytes of data past the end of the pixel data.)
	if(!err) { 
		uint8_t byte;
		read = fread(&byte, sizeof(uint8_t), 1, fp);
		if(read != 0) {
		    fprintf(stderr, "Stray bytes at the end of image file '%s'\n",
			    filename);
		    err = TRUE;
		}
    }

    // We're winners... -------------------------------------------------------------------
    if(!err) { 
    	//image will be returned.
		im = tmp_im; 
		tmp_im = NULL; 
	}
	if(fp) {
		fclose(fp);
    }

    if(tmp_im != NULL) {
		free(tmp_im->comment); // Remember, you can always free(NULL)
		free(tmp_im->data);
		free(tmp_im);
    }

    return im;

}

// -------------------------------------------------------------- Image_save
int Image_save(const char * filename, Image * image) {
	int err = FALSE; 
	FILE * fp = NULL;
	size_t written = 0;
	uint8_t * buffer = NULL;  

	// Attempt to open file for writing
    fp = fopen(filename, "wb");
    if(fp == NULL) {
	fprintf(stderr, "Failed to open '%s' for writing\n", filename);
	return FALSE; // No file ==> out of here.
    }
    
    // Prepare the header
    ImageHeader header;
    header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
    header.width = image->width;
    header.height = image->height;
    header.comment_len = strlen(image->comment) + 1;

    // Write the header
    if(!err) {  
		written = fwrite(&header, sizeof(header), 1, fp);
		if(written != 1) {
		    fprintf(stderr, 
			    "Error: only wrote %zd of %zd of file header to '%s'\n",
			    written, sizeof(header), filename);
		    err = TRUE;	
		}
    }

    // Write the comment
    if (!err) {
    	written = fwrite(image->comment, sizeof(char), header.comment_len, fp);
    	if(written != header.comment_len) {
    		fprintf(stderr, "Failed to write comment to file\n");
			err = TRUE;
    	}
    }

    // Before writing, we'll need a write buffer
    if(!err) { 
		buffer = malloc(header.width);
		if(buffer == NULL) {
		    fprintf(stderr, "Error: failed to allocate write buffer\n");
		    err = TRUE;
		} 
	}

    if(!err) { // Write pixels	
		uint8_t * read_ptr = image->data;	
		int row, col; // row and column
		for(row = 0; row < header.height && !err; ++row) {
		    uint8_t * write_ptr = buffer;
		    for(col = 0; col < header.width; ++col) {
				*write_ptr++ = *read_ptr++; 
		    }
		    // Write line to file
		    written = fwrite(buffer, sizeof(uint8_t), header.width, fp);
		    if(written != header.width) {
				fprintf(stderr, "Failed to write pixel data to file\n");
				err = TRUE;
		    }
		}
    }
    
    // Cleanup
    free(buffer);
    if(fp)
	fclose(fp);
	return !err;
}

// -------------------------------------------------------------- Image_free
void Image_free(Image * image) {
	 // Cleanup-----------------------------------------------------------------------------
    if(image != NULL) {
		free(image->comment); // Remember, you can always free(NULL)
		free(image->data);
		free(image);
	}
}

// -------------------------------------------------------------- linearNormalization
void linearNormalization(int width, int height, uint8_t * intensity) {
	int i = 0;
	uint8_t max = 0;
	uint8_t min = 255;
	for (i = 0; i < height * width; i++) {
		if (max < intensity[i]) max = intensity[i];
		if (min > intensity[i]) min = intensity[i];
	}
	for (i = 0; i < height * width; i++) {
		intensity[i] = (intensity[i] - min) * 255.0 / (max - min);
	}
}

// -------------------------------------------------------------- checkValid

int checkValid(ImageHeader * header) {
	// (2.b) Make sure that the magic_number in the header is correct
    if (header->magic_number != ECE264_IMAGE_MAGIC_NUMBER) return FALSE;
    //(2.c) Make sure that neither the width nor height is zero
    if (header->width == 0 || header->height == 0) return FALSE;
    //(2.d) Make sure that the comment length is not zero. (Remember, it includes the null-byte.)
    if (header->comment_len == 0) return FALSE;
    // We're winners!!!
    return TRUE;
}

// -------------------------------------------------------------- printHeader

void printHeader(ImageHeader * header) {
	printf("Printing Imageheader information:\n");
    printf("  file magic_number : %x\n", header->magic_number);
    printf("  width: %d\n", header->width);
    printf("  height: %d\n", header->height);
    printf("  comment length: %d\n", header->comment_len);
}
