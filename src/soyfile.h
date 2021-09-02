#ifndef SOY_FILE_H
#define SOY_FILE_H

#include "soycore.h"
#include "soystring.h"

typedef enum enum_fileType {
	BYT,
	TXT,
	BMP
} fileType;

#define MAX_SIZE_PNG (8 * 1024 * 1024)

static char DIRBUFFER[S_MAX_DIR];



const char* soy_file_current_dir(char* buffer, unsigned int buffersize) {
	_getcwd(buffer, buffersize-1);
	return DIRBUFFER;
} 

FILE* soy_file_open_read(const char* filepath) {
	FILE* file = NULL;
	if(soy_cstring_len(filepath, S_MAX_DIR) != 0) {
		file = fopen(filepath, "r");
		SLOGERR(file);
	} 
	return file; 
} 
 
FILE* soy_file_open_write(const char* filepath) {
	FILE* file = NULL;
	if(soy_cstring_len(filepath, S_MAX_DIR) != 0) {
		file = fopen(filepath, "w");
		SLOGERR(file);
	} 
	return file; 
} 
  
FILE* soy_file_open_append(const char* filepath) {
	FILE* file = NULL;
	if(soy_cstring_len(filepath, S_MAX_DIR) != 0) {
		file = fopen(filepath, "a");
		SLOGERR(file);
	} 
	return file; 
} 

FILE* soy_file_open_read_bin(const char* filepath) {
	FILE* file = NULL;
	if(soy_cstring_len(filepath, S_MAX_DIR) != 0) {
		file = fopen(filepath, "r");
		SLOGERR(file);
	} 
	return file; 
} 
 
FILE* soy_file_open_write_bin(const char* filepath) {
	FILE* file = NULL;
	if(soy_cstring_len(filepath, S_MAX_DIR) != 0) {
		file = fopen(filepath, "w");
		SLOGERR(file);
	} 
	return file; 
} 
  
FILE* soy_file_open_append_bin(const char* filepath) {
	FILE* file = NULL;
	if(soy_cstring_len(filepath, S_MAX_DIR) != 0) {
		file = fopen(filepath, "a");
		SLOGERR(file);
	} 
	return file; 
} 

flag soy_file_close(FILE* file) {
	flag ret = UNDEF;
	if(file) { 
		fclose(file);
		ret = TRUE;
	} 
	return ret;
}

flag soy_file_delete(const char* filepath) {
	flag ret = UNDEF;
	ret = remove(filepath);
	return ret;
}

unsigned long int soy_file_get_pos(FILE* file) {
	return ftell(file);
}
 
flag soy_file_set_pos(FILE* file, unsigned long pos) {
	flag ret = UNDEF;
	fseek(file, 0, pos);	 
	return ret;
}

unsigned long int soy_file_get_size(const char* filepath) {
	FILE* file = NULL;
	unsigned long int ret = 0;
	unsigned long int lastPos = 0;
	if(soy_cstring_len(filepath, S_MAX_DIR) != 0) {
		file = fopen(filepath, "r");
		SLOGERR(file);
		lastPos = soy_file_get_pos(file);
		fseek(file, 0, SEEK_END);
		ret = ftell(file);
		fseek(file, 0, lastPos);
	}
	return ret;
}

flag soy_file_write_line(const char* text, FILE* file) {
	flag ret = UNDEF;
	if(file && text) {
		fputs(text, file);
		ret = TRUE;
	}
	return ret;
}

/* (while !soy_file_read_line)... */
flag soy_file_read_line(char* buffer, unsigned int buffersize, FILE* file) {
	flag ret = UNDEF;
	if(buffer && file) {
		if(fgets(buffer, buffersize-1, file) == NULL) {
			ret = FALSE;
		} else {
			ret = TRUE;
		}
	}
	return ret;
}

/* (while !soy_file_read_bytes)...) */
flag soy_file_read_bytes(unsigned char* buffer, unsigned int stride, unsigned int maxSize, FILE* file) {
	flag ret =  UNDEF;
	if(buffer && file && stride) {
		ret = fread(buffer, stride, maxSize, file);
	}
	return ret;
}

#endif
