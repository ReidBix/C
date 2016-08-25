//g++ -O2 -Wall -std=c++11 vmm.cpp -o vmm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>

using namespace std;

typedef struct {
	int page;
	int frame;
	int access;
	int full = 0;
} buffer;

typedef struct {
	int page;
	int access;
	int frame;
	int full = 0;
} page;

typedef struct{
	int page;
	char arr[256];
	int full = 0;
} physMem;

buffer TLB[4];
page pageTable[16];
physMem pMem[20];
int framesFull = 0;
int TLBFull = 0;
vector<int> addrs;


int main(int argc, char**argv){
	ifstream infile("addresses.txt");
	int n;
	int TLBHits = 0;
	double TLBHitRatio;
	int PageFaults = 0;
	while (infile >> n){
		addrs.push_back(n);
	}
	for (unsigned i=0; i<addrs.size(); i++) {
		int va = addrs.at(i);
		unsigned pOffset = va & 0xFF;
		int pNumber = (va>>8) & 0xFF;

		int finalFrame = pOffset;

		int hit = 0;
		int TLBframe = 0;
		int entry = 0;
		for(int a=0; a<4;a++){
			if(TLB[a].page == pNumber){
				TLBframe = TLB[a].frame;
				entry = a;
				hit = 1;
				break;
			}
		}
		if (hit){
			TLBHits += 1;
			printf("TLB HIT: page %d is contained in frame %d, found in TLB entry %d\n",pNumber,TLBframe,entry);
		} else {
			printf("TLB MISS: page %d is not in the TLB\n",pNumber);
		}
		int x = pageTable[pNumber].full;
		if (x == 1 && !hit){
			finalFrame = pageTable[pNumber].frame;
			printf("FOUND: page %d is contained in frame %d\n",pNumber,pageTable[pNumber].frame);
		}
		else if (!hit){
			PageFaults += 1;
			printf("PAGE FAULT: virtual address %d contained in page %d caused a page fault!\n", va, pNumber);
			int frame = 0;
			int empty = 0;
			if (!framesFull){
				for (int j=0; j<8; j++) {
					frame = j;
					if (!pMem[frame].full){
						empty = 1;
						break;
					}
				}
			}
			if (empty) {
				pMem[frame].page = pNumber;
				pMem[frame].full = 1;
				pageTable[pNumber].frame = frame;
				if (frame == 7){
					framesFull = 1;
				}
				printf("LOADED: page %d is loaded into frame %d\n", pNumber, frame);
				finalFrame = frame;

			    ifstream myFile ("BACKING_STORE.bin", ios::in | ios::binary);
			    if (!myFile) {
			        myFile.clear();
			    }
			    myFile.seekg (256*pNumber);
			    myFile.read (pMem[frame].arr, 256);


			} else {
				int pageReplace = pMem[0].page;
				int frameReplace = 0;
				int minTime = pageTable[pMem[0].page].access;
				for (int l=1;l<8;l++){
					int nextTime = pageTable[pMem[l].page].access;
					if(nextTime < minTime){
						minTime = nextTime;
						pageReplace = pMem[l].page;
						frameReplace = l;
					}
				}
				pageTable[pageReplace].full = 0;
				pMem[frameReplace].page = pNumber;
				pageTable[pNumber].frame = frameReplace;
				printf("LOADED: page %d is loaded into frame %d\n", pNumber, frameReplace);
				finalFrame = frameReplace;

			    ifstream myFile ("BACKING_STORE.bin", ios::in | ios::binary);
			    if (!myFile) {
			        myFile.clear();
			    }
			    myFile.seekg (256*pNumber);
			    myFile.read (pMem[frame].arr, 256);

			}
		}
		if (!hit){
			int TLBentry = 0;
			int TLBempty = 0;
			int finalEntry;
			if (!TLBFull){
				for (int b=0; b<4; b++) {
					TLBentry = b;
					if (!TLB[b].full){
						TLBempty = 1;
						break;
					}
				}
			}
			if (TLBempty) {
				TLB[TLBentry].page = pNumber;
				TLB[TLBentry].frame = finalFrame;
				TLB[TLBentry].full = 1;
				TLB[TLBentry].access = i;
				if (TLBentry == 3){
					TLBFull = 1;
				}
				finalEntry = TLBentry;
			} else {
				int entryReplace = 0;
				int minTime = TLB[0].access;
				for (int c=1;c<4;c++){
					int nextTime = TLB[c].access;
					if(nextTime < minTime){
						minTime = nextTime;
						entryReplace = c;
					}
				}
				TLB[entryReplace].page = pNumber;
				TLB[entryReplace].frame = finalFrame;
				TLB[entryReplace].access = i;
				finalEntry = entryReplace;
			}
			printf("TLB LOAD: frame %d containing page %d is stored in TLB entry %d\n",TLB[finalEntry].frame,pNumber,finalEntry);
		}
		pageTable[pNumber].access = i;
		pageTable[pNumber].full = 1;
		printf("\n");
	}
	printf("Total address references: %d\n", (int)addrs.size());
	printf("TLB Hits: %d\n",TLBHits);
	TLBHitRatio = double(TLBHits) / addrs.size();
	printf("TLB Hit Ratio: %f\n",TLBHitRatio);
	printf("Page Faults: %d\n",PageFaults);

	printf("\n");
	printf("The contents of the page table after simulation:\n");
	for (int i=0;i<16;i++){
		page p = pageTable[i];
		if (p.full == 0){
			printf("Page %d not in physical memory\n",i);
		} else {
			printf("Page %d in frame %d\n", i,p.frame);
		}
	}
	printf("\nThe contents of each frame:\n");
	for (int i=0;i<8;i++){
		printf("Frame %d contains page %d\n",i,pMem[i].page);
	}

}