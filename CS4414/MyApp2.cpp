#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "disk.h"
#include <string>
#include <iostream>
#include <algorithm>

// g++ -O2 -w -std=c++11 myApp.cpp disk.c -o exec

using namespace std;

int make_fs(char *disk_name);
int mount_fs(char *disk_name);
int dismount_fs(char *disk_name);
int fs_open(char *name);
int fs_close(int fildes);
int fs_create(char *name);
int fs_delete(char *name);
int fs_read(int fildes, void *buf, size_t nbyte);
int fs_write(int fildes, void *buf, size_t nbyte);
int fs_get_filesize(int fildes);
int fs_lseek(int fildes, off_t offset);
int fs_truncate(int fildes, off_t length);

size_t nbyte;
off_t offset;
off_t length;
int temp;

#define BUFFER_SIZE 80

struct superblock
{
  char directory[4]; //Directory
  char FAT[4]; //FAT
  char data[4];
  char unused[4];
};

struct directoryEntry //Blocks 1-8
{
  string entry;
  char status[2];  //Free or allocated
  char blockNum[3]; // 1st data block number????
  char fn[5]; // File Name
  char len[4]; //Length of file
};

struct FATEntry //Blocks 9-16 (References Blocks 32-63)
{
  string entry;
  char status[2]; //Free or allocated
  char blockNum[4]; //FIRST BLOCK OF THE FILE!
  //9[0] = 32, 9[1] = 33, 10[0] = 36... 16[0] = 60...16[3] = 63
};

struct openFileEntry //For Open File Table
{
  char status[2];
  unsigned fileptr;
  unsigned index;
};

directoryEntry directory[8];
FATEntry FAT[64];
openFileEntry OFT[4];

unsigned i;
unsigned iii;

int status;

int totalNum;

char tempBuf[BUFFER_SIZE];

int fda, fdb, fdc, fdd, fde; // 5 file descriptors

int main() {
  
 
  make_fs("tcs");
  mount_fs("tcs");

  fs_create("fc");
  fdc = fs_open("fc");
  char bufc[] = "I love computer programming because I can ask computers to do something for me";
  nbyte = 78;
  fs_write(fdc,&bufc,nbyte);

  fs_lseek(fdc, -78);
  nbyte = 78;
  int totalNum = fs_read(fdc,tempBuf,nbyte);
  printf("total number of bytes read from file fc = %d\n", totalNum); 
  for (i = 0; i < nbyte; i++)
    printf("%c",tempBuf[i]); // "I love computer programming because I can ask computers to do something for me"
  printf("\n");

  fs_lseek(fdc, -76);
  char bufc_new[] = "like ";
  nbyte  = strlen(bufc_new);
  fs_write(fdc, &bufc_new, nbyte);
  fs_lseek(fdc, -7);
  length = fs_get_filesize(fdc);
  printf("file size of file fc = %d\n", (int) length); // file size of file fc = 78

  nbyte = 71;
  totalNum = fs_read(fdc,tempBuf,nbyte);
  printf("total number of bytes read from file fc = %d\n", totalNum); 
  for (i = 0; i < nbyte; i++)
    printf("%c",tempBuf[i]); // "I like computer programming because I can ask computers to do something" 
  printf("\n");

    dismount_fs("tcs");
 
  return 0;
}

int make_fs(char *disk_name){
  int status;
  unsigned i;

  //printf("\nMAKE_FS: (START)\n");
  status = make_disk(disk_name);
  if (!status){
      //printf("New disk created with name %s!\n", disk_name);
  } else {
    //printf("ERROR: New disk not created!\n");
    //printf("MAKE_FS: (END)\n\n");
    return -1;
  }

  status = open_disk(disk_name);
  if (!status){
      //printf("Disk %s opened!\n", disk_name);
  } else {
    //printf("ERROR: Disk %s not opened!\n", disk_name);
    //printf("MAKE_FS: (END)\n\n");
    return -1;
  }

  for (i = 0; i < 17; ++i){
    if (i == 0){
      status = block_write(i,"010809163263xxxx");
    }
    if (i > 0 && i < 9){
      status = block_write(i,"0000000000000000");
      if (status){
        //printf("ERROR: Directory not initialized!\n");
        //printf("MAKE_FS: (END)\n\n");
        return -1;
      }
    }
    if (i >= 9 && i < 17){
      status = block_write(i,"0xxx0xxx0xxx0xxx");
      if (status){
        //printf("ERROR: FAT not initialized!\n");
        //printf("MAKE_FS: (END)\n\n");
        return -1;
      }
    }     
  }
  if (!status){
      //printf("Disk %s initialized!\n", disk_name);
  } else {
    //printf("ERROR: Disk %s not initialized!\n", disk_name);
    //printf("MAKE_FS: (END)\n\n");
    return -1;
  }

  //Close Disk
  status = close_disk();
  if (!status){
      //printf("Disk closed!\n");
  } else {
    //printf("ERROR: Disk not closed!\n");
    //printf("MAKE_FS: (END)\n\n");
    return -1;
  }

  //Success!
  //printf("MAKE_FS: (END)\n\n");
  return 0;
}


int mount_fs(char *disk_name){
  int status;
  unsigned i, j;
  char tempBuf[80];
  char str[80];
  int c = 2;
  unsigned dS, dF, fS, fF;

  //printf("\nMOUNT_FS: (START)\n");

  //Open Disk
  status = open_disk(disk_name);
  if (!status){
      //printf("Disk %s opened!\n", disk_name);
  } else {
    //printf("ERROR: Disk %s not opened!\n", disk_name);
    //printf("MOUNT_FS: (END)\n\n");
    return -1;
  }

  //Load directory and FAT into memory (use block_read)
  block_read(0,tempBuf);
  strncpy (str, tempBuf, c);
  str[c] = '\0';
  sscanf(str, "%d", &dS);
  strncpy (str, tempBuf+2, c);
  str[c] = '\0';
  sscanf(str, "%d", &dF);
  strncpy (str, tempBuf+4, c);
  str[c] = '\0';
  sscanf(str, "%d", &fS);
  strncpy (str, tempBuf+6, c);
  str[c] = '\0';
  sscanf(str, "%d", &fF);
  //printf("%d, %d, %d, %d\n",dS,dF,fS,fF);

  int ii = 0;
  for (i = dS; i <= dF; ++i){
    status = block_read(i,tempBuf);
    string s, b, f, l;
    directoryEntry newEntry;
    newEntry.entry = string(tempBuf).substr(0,16);
    string e = newEntry.entry;
    s = e.substr(0, 1);
    b = e.substr(1, 2);
    f = e.substr(3, 4);
    f.erase(remove(f.begin(), f.end(), '?'), f.end());
    l = e.substr(7, 3);
    strcpy(newEntry.status, s.c_str());
    strcpy(newEntry.blockNum, b.c_str());
    strcpy(newEntry.fn, f.c_str());
    strcpy(newEntry.len, l.c_str());
    //printf("%s,%s,%s,%s\n",newEntry.status,newEntry.blockNum,newEntry.fn,newEntry.len);
    directory[ii] = newEntry;
    ii++;
  }
  for (i = fS; i <= fF; ++i){
    status = block_read(i,tempBuf);
    for (j = 0; j < 4; ++j){
      FATEntry newEntry;
      newEntry.entry = string(tempBuf).substr(0+j*4,4);
      string e = newEntry.entry;
      string a(e.substr(0, 1));
      string b(e.substr(1, 3));
      strcpy(newEntry.status, a.c_str());
      strcpy(newEntry.blockNum, b.c_str());
      //printf("%s,%s\n",newEntry.status,newEntry.blockNum);
      FAT[32+(i-9)*4+j] = newEntry;
    }
  }
  //Create an OFT in memory
  for (i = 0; i < 4; ++i){
    string s = "0";
    strcpy(OFT[i].status, s.c_str());
    OFT[i].fileptr = 0;
    OFT[i].index = 0;
  }

  //CHECK FOR VALID FILE SYSTEM

  //Success!
  //printf("Valid File System found!\n");
  //printf("MOUNT_FS: (END)\n\n");
  return 0;
}


int dismount_fs(char *disk_name){
  int status = 0;
  unsigned i, j;

  //printf("\nDISMOUNT_FS: (START)\n");

  for (i = 1; i <= 8; ++i){
    char e[17];
    string s = string(directory[i-1].status);
    string b = string(directory[i-1].blockNum);
    while (b.length() < 2){
      b.insert(0, 1, '0');
    }
    string f = string(directory[i-1].fn);
    while (f.length() < 4){
      f.insert(f.end(), 1, '?');
    }
    string l = string(directory[i-1].len);
    while (l.length() < 3){
      l.insert(0, 1, '0');
    }
    string whole = s + b + f + l;
    //cout << whole << endl;
    strcpy(e, whole.c_str());
    //printf("Writing %s to the directory at block %d\n", e, i-1);
    status = block_write(i,e);
    if (status){
        //printf("ERROR: Directory not written!\n");
        //printf("DISMOUNT_FS: (END)\n\n");
        return -1;
    }
  }
  for (i = 9; i<=16; ++i){
    string entry = "";
    char e[17];
    for (j = 0; j < 4; ++j){
      FATEntry f = FAT[32+(i-9)*4+j];
      string s = string(f.status);
      string b = string(f.blockNum);
      while (b.length() < 3){
        b.insert(0, 1, '0');
      }
      entry = entry + s + b;
    }
    strcpy(e, entry.c_str());
    //printf("Writing %s to the FAT File at block %d\n", e, i);
    status = block_write(i,e);
    if (status){
        //printf("ERROR: FAT not written!\n");
        //printf("DISMOUNT_FS: (END)\n\n");
        return -1;
    }
  }

  status = close_disk();
  if (!status){
      //printf("Disk closed!\n");
  } else {
    //printf("ERROR: Disk not closed!\n");
    //printf("DISMOUNT_FS: (END)\n\n");
    return -1;
  }

  return 0;
}


int fs_open(char *name){
  unsigned i;
  unsigned found = 0;

  //printf("\nFS_OPEN: (START)\n");

  for (i = 0; i < 8; ++i){
    //puts(directory[i].fn);
    if(strcmp(directory[i].fn, name) == 0){
      found = i;
      break;
    } else {
      if (i == 7 && found == 0){
        //printf("ERROR: File '%s' with name cannot be found!\n", name);
        //printf("FS_OPEN: (END)\n\n");
        return -1;
      }
    }
  }
  for (i = 0; i < 4; ++i){
    if (OFT[i].index == found){
      if (strcmp(OFT[i].status, "1") == 0){
        //printf("ERROR: File '%s' already open at index %i in OFT!\n", name,i);
        //printf("FS_OPEN: (END)\n\n");
        return -1;
      }
    }
  }
  for (i = 0; i < 4; ++i){
    if(strcmp(OFT[i].status, "0") == 0){
      strcpy(OFT[i].status, "1");
      OFT[i].fileptr = 0;
      OFT[i].index = found;
      //printf("Filesystem '%s' opened and stored at index %i in OFT\n",name,i);
      //printf("FS_OPEN: (END)\n\n");
      return i;
    } else {
      if (i == 3) {
        //printf("ERROR: Already 4 file descriptors active!\n");
        //printf("FS_OPEN: (END)\n\n");
        return -1;
      }
    }
  }
  //printf("FS_OPEN: (END)\n\n");
  return -1;
}


int fs_close(int fildes){
  //printf("\nFS_CLOSE: (START)\n");

  if (fildes > 3 || fildes < 0){
    //printf("ERROR: File descriptor does not exist!\n");
    //printf("FS_CLOSE: (END)\n\n");
    return -1;
  }
  if(strcmp(OFT[fildes].status, "0") == 0){
    //printf("ERROR: File is already currently open!\n");
    //printf("FS_CLOSE: (END)\n\n");
    return -1;
  }
  strcpy(OFT[fildes].status, "0");
  
  //printf("FS_CLOSE: (END)\n\n");
  return 0;
}


int fs_create(char *name){
  unsigned i;
  char e[5];

  //printf("\nFS_CREATE: (START)\n");

  if (strlen(name) > 4){
    //printf("ERROR: File name is too long!\n");
    //printf("FS_CREATE: (END)\n\n");
    return -1;
  } else {
    strcpy(e,name);
  }
  for (i = 0; i < 8; ++i){
    if(strcmp(directory[i].fn, name) == 0){
      //printf("ERROR: File with name already exists!\n");
      //printf("FS_CREATE: (END)\n\n");
      return -1;
    }
    if(strcmp(directory[i].status, "0") == 0){
      directoryEntry newEntry;
      string s = "1";
      string b = "00";
      string n = string(name);
      string l = "000";
      strcpy(newEntry.status, s.c_str());
      strcpy(newEntry.blockNum, b.c_str());
      strcpy(newEntry.fn, n.c_str());
      strcpy(newEntry.len, l.c_str());
      string entry = s + b + n + l;
      newEntry.entry = entry;
      directory[i] = newEntry;
      //printf("New directory entry '%s' created at index %d in directory\n",n.c_str(),i);
      //printf("FS_CREATE: (END)\n\n");
      return 0;
    } else {
      if (i == 7){
        //printf("ERROR: Already 8 files present in root directory!\n");
        //printf("FS_CREATE: (END)\n\n");
        return -1;
      }
    }
  }
  //printf("FS_CREATE: (END)\n\n");
  return 0;
}


int fs_delete(char *name){
  unsigned i;
  unsigned found = 0;
  
  //printf("\nFS_DELETE: (START)\n");
  for (i = 0; i < 8; ++i){
    //puts(directory[i].fn);
    if(strcmp(directory[i].fn, name) == 0){
      found = i;
      break;
    } else {
      if (i == 7 && found == 0){
        //printf("ERROR: Name does not exist!\n");
        //printf("FS_DELETE: (END)\n\n");
        return -1;
      }
    }
  }
  for (i = 0; i < 4; ++i){
    if (OFT[i].index == found){
      if (strcmp(OFT[i].status, "1") == 0){
        //printf("ERROR: File is currently open!\n");
        //printf("FS_DELETE: (END)\n\n");
        return -1;
      }
    }
  }
  int cur = 0;
  int n;
  sscanf(directory[found].len, "%d", &n);
  int next;
  int prev;
  for (cur = 0; cur < n;){ 
    if (cur == 0){
      sscanf(directory[found].blockNum, "%d", &prev);
      //printf("Block being reset %d\n", prev);
      sscanf(FAT[prev].blockNum, "%d", &next);
      strcpy(directory[found].len, "000");
      strcpy(directory[found].blockNum, "00");
      strcpy(directory[found].status, "0");
      strcpy(directory[found].fn, "0000");
      //printf("%d\n",prev);
      //printf("%d\n",next);
    } else {
      sscanf(FAT[prev].blockNum, "%d", &prev);
      //printf("Block being reset %d\n", prev);
      strcpy(FAT[prev].blockNum, "000");
      strcpy(FAT[prev].status, "0");
      sscanf(FAT[next].blockNum, "%d", &next);
    }
    //printf("blockNow = %d, blockNext = %d, cur = %d, n = %d\n", prev, next, cur, n);
    cur += 16;
  }
  //printf("FS_DELETE: (END)\n\n");
  return 0;
}


int fs_read(int fildes, void *buf, size_t nbyte){
  //printf("\nFS_READ: (START)\n");
  int total = 0;
  string whole = "";

  if (fildes > 3 || fildes < 0){
    //printf("ERROR: File descriptor does not exist!\n");
    //printf("FS_READ: (END)\n\n");
    return -1;
  }
  if(strcmp(OFT[fildes].status, "0") == 0){
    //printf("ERROR: File is not open!\n");
    //printf("FS_READ: (END)\n\n");
    return -1;
  }
  unsigned fp = OFT[fildes].fileptr;
  unsigned cur = 0;
  int ind = OFT[fildes].index;

  //printf("A\n");
  //printf("filepointer = %d, cur = %d, nbyte = %d, total = %d\n",fp, cur, nbyte, total);
  int next;
  sscanf(directory[ind].blockNum, "%d", &next);
  //printf("%d\n",next);
  cur += 16;
  //SKIP FOR FILE POINTER
  for (cur = 16; cur < fp;){
    if (cur > fp){
      break;
    }
    //printf("filepointer = %d, cur = %d, nbyte = %d, total = %d\n",fp, cur, nbyte, total);
    sscanf(FAT[next].blockNum, "%d", &next);
    //printf("%d\n",next);
    cur += 16;
  }
  //printf("B\n");
  cur -= 16;
  //printf("filepointer = %d, cur = %d, nbyte = %d, total = %d\n",fp, cur, nbyte, total);
  unsigned s = fp - cur;

  //NEW LINE
  char *bufC = (char*)buf;

  block_read(next, bufC);
  string buffer = string(bufC).substr(0,16);
  //printf("C\n");
  if (s < 16 && s%16 != 0){
    string b = buffer.substr(s, 16+cur-fp);
    whole = whole + b;
    //cout << b << endl;
    total += s;
  } else if (s%16 == 0){
    whole = whole + buffer;
    //cout << buffer << endl;
    total += 16;
  }
  //printf("D\n");
  //printf("%d\n",nbyte-s);
  unsigned k;
  for (k = 0; k < nbyte-s;){
    //last X bytes (less than 16)
    //printf("s = %d, cur = %d, nbyte = %d, total = %d\n",s, cur, nbyte, total);
    sscanf(FAT[next].blockNum, "%d", &next);
    block_read(next, bufC);
    string buffer = string(bufC).substr(0,16);
    if (nbyte-s < 16) {
      //printf("AAA\n");
      if (cur == 0){
        total -= 16;
      }
      string b = buffer.substr(0, nbyte-s);
      whole = whole + b;
      //cout << b << endl;
      //printf("CCC %d\n",nbyte-s);
      total += nbyte-s;
      //printf("s = %d, cur = %d, nbyte = %d, total = %d\n",s, cur, nbyte, total);
      if (fp == 0 && k == 0 && nbyte < 16){
        //printf("BBB\n");
        whole = b;
        total = nbyte;
        //printf("s = %d, cur = %d, nbyte = %d, total = %d\n",s, cur, nbyte, total);
      }
      break;
    }
    //reading whole blocks
    whole = whole + buffer;
    //cout << buffer << endl;
    total += 16;
    //printf("s = %d, cur = %d, nbyte = %d, total = %d\n",s, cur, nbyte, total);
    s += 16;
  }
  //cout << whole << endl;
  OFT[fildes].fileptr = fp + total;
  //printf("File pointer now at %d\n",OFT[fildes].fileptr);
  strcpy(bufC, whole.c_str());
  //printf("FS_READ: (END)\n\n");
  return total;
}


int fs_write(int fildes, void *buf, size_t nbyte){
  //printf("\nFS_WRITE: (START)\n");
  unsigned i, j;
  int found = 0;
  int lastFound = 0;
  int total = 0;
  char b[17];

  if (fildes > 3 || fildes < 0){
    //printf("ERROR: File descriptor does not exist!\n");
    //printf("FS_WRITE: (END)\n\n");
    return -1;
  }
  if(strcmp(OFT[fildes].status, "0") == 0){
    //printf("ERROR: File is not open!\n");
    //printf("FS_WRITE: (END)\n\n");
    return -1;
  }
  unsigned fp = OFT[fildes].fileptr;
  int ind = OFT[fildes].index;
  int n;
  sscanf(directory[found].len, "%d", &n);

  //printf("filepointer = %d, nbyte = %d, ind = %d\n",fp,nbyte, ind);
  for (j = 0; j < nbyte;){
    //GET FREE BLOCK
    if (j%16 == 0){
      //Go to next available block...
      //Store in FAT block number or if 1st instance, directory entry
      for (i = 32; i <= 63; ++i){
        if( strcmp(FAT[i].status, "0") == 0 ){
          found = 1;
          //printf("Free block found in FAT at index %d\n",i);
          //Update directory or FAT
          string n = to_string(i);
          if (j == 0){
            strcpy(directory[ind].blockNum, n.c_str());
            //printf("1st block number for index %d in directory is %d\n",ind,i);
            lastFound = i;
          } else {
            strcpy(FAT[lastFound].blockNum, n.c_str());
            //printf("Block number %d now leads to block number %d\n",lastFound,i);
            lastFound = i;
          }
          strcpy(FAT[i].status, "1");
          break;
        } else {
          if (i == 63 && found == 0){
            //printf("ERROR: No free blocks were found!\n");
            lastFound = 0;
            return total;
          }
        }
      }
    }
    //WRITE TO BLOCK
    int q;
    if (nbyte - j > 16) {
      q = 16;
    } else {
      q = nbyte - j;
    }
    //printf("q = %d\n",q);
    //printf("Writing %d bytes to block %d\n", q, lastFound);

    //NEW LINE
    char* bufC = (char*)buf;

    strcpy(FAT[lastFound].blockNum, "XXX");
    string bytes = string(bufC).substr(j,16);
    strcpy(b, bytes.c_str());
    block_write(lastFound,b);
    //printf("%d\n",lastFound);
    j += 16;
    total = total + q;
  }
  string t = to_string(total);
  strcpy(directory[ind].len, t.c_str());
  OFT[fildes].fileptr = fp + total;
  //printf("File pointer now at %d\n",OFT[fildes].fileptr);
  //printf("FS_WRITE: (END)\n\n");
  return total;
}


int fs_get_filesize(int fildes){
  //printf("\nFS_GET_FILESIZE: (START)\n");
  if (fildes > 3 || fildes < 0){
    //printf("ERROR: File descriptor does not exist!\n");
    //printf("FS_GET_FILESIZE: (END)\n\n");
    return -1;
  }
  if(strcmp(OFT[fildes].status, "0") == 0){
    //printf("ERROR: File is not open!\n");
    //printf("FS_GET_FILESIZE: (END)\n\n");
    return -1;
  }
  int ind = OFT[fildes].index;
  int n;
  sscanf(directory[ind].len, "%d", &n);

  //printf("File size is %d\n", n);
  //printf("FS_GET_FILESIZE: (END)\n\n");
  return n;
}


int fs_lseek(int fildes, off_t offset){
  //printf("\nFS_LSEEK: (START)\n");
  if (fildes > 3 || fildes < 0){
    //printf("ERROR: File descriptor does not exist!\n");
    //printf("FS_LSEEK: (END)\n\n");
    return -1;
  }
  if(strcmp(OFT[fildes].status, "0") == 0){
    //printf("ERROR: File is not open!\n");
    //printf("FS_LSEEK: (END)\n\n");
    return -1;
  }
  unsigned fp = OFT[fildes].fileptr;
  int n = fs_get_filesize(fildes);
  //printf("File pointer currently at %d\n",OFT[fildes].fileptr);
  //printf("Attempting to move %d\n",offset);
  if (fp + offset < 0){
    //printf("ERROR: Out of bounds, before beginning of file!\n");
    //printf("FS_LSEEK: (END)\n\n");
    return -1;
  }
  if (fp + offset > n){
    //printf("ERROR: Out of bounds, after end of file!\n");
    //printf("FS_LSEEK: (END)\n\n");
    return -1;
  }
  OFT[fildes].fileptr = fp + offset;
  //printf("File pointer now at location %d\n", OFT[fildes].fileptr);
  //printf("FS_LSEEK: (END)\n\n");
  return 0;
}


int fs_truncate(int fildes, off_t length){
  //printf("\nFS_TRUNCATE: (START)\n");
  if (fildes > 3 || fildes < 0){
    //printf("ERROR: File descriptor does not exist!\n");
    //printf("FS_TRUNCATE: (END)\n\n");
    return -1;
  }
  if(strcmp(OFT[fildes].status, "0") == 0){
    //printf("ERROR: File is not open!\n");
    //printf("FS_TRUNCATE: (END)\n\n");
    return -1;
  }
  OFT[fildes].fileptr = 0;
  unsigned cur = 0;
  int ind = OFT[fildes].index;
  unsigned n = fs_get_filesize(fildes);
  if (length > n){
    //printf("ERROR: Length is larger than file size!\n");
    //printf("FS_TRUNCATE: (END)\n\n");
    return -1;
  }
  int next;
  int prev;
  sscanf(directory[ind].blockNum, "%d", &next);
  sscanf(directory[ind].blockNum, "%d", &prev);
  //printf("%d\n",next);
  for (cur = 0; cur < n;){
    if (cur < length){
      //printf("Block being kept %d\n", prev);
      sscanf(FAT[next].blockNum, "%d", &prev);
      sscanf(FAT[next].blockNum, "%d", &next);
    }
    else if (cur >= length){
      if (length == 0){
        strcpy(directory[ind].len, "000");
        strcpy(directory[ind].blockNum, "00");
      }
      //printf("Block being reset %d\n", prev);
      strcpy(FAT[prev].blockNum, "000");
      strcpy(FAT[prev].status, "0");
      //printf("filepointer = %d, cur = %d, ind = %d\n",fp, cur, ind);
      sscanf(FAT[next].blockNum, "%d", &prev);
      sscanf(FAT[next].blockNum, "%d", &next);
    }
    cur += 16;
  }
  OFT[fildes].fileptr = 0;
  string newN = to_string((length));
  strcpy(directory[ind].len, newN.c_str());
  //printf("FS_TRUNCATE: (END)\n\n");
  return 0;
}
