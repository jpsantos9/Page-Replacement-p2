#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>
#include <algorithm>

enum class PageRepAlgo{
    MRU,
    LRU,
    MFU,
    LFU
};

void printList (std::vector<int> List){
    std::cout<<"[";
    for (elem : List) {
        std::cout<<elem<<", ";
    }
    std::cout<<"]"<<std::endl;
}

std::vector<int> clearList (int frameBufferSize){
    std::vector<int> temp;
    for (int i=0; i<frameBufferSize; i++){
        temp.push_back(-1);
    }
    return temp;
}

bool inBuffer (int x, std::vector<int> buffer){
    int counter=0;
    for (elem : buffer){
        if (x==elem){
            counter++;
        }
    }
    if (counter>0){
        return true;
    } else {
        return false;
    }
}

std::vector<int> placeElem (int elem, int pointer, std::vector<int> buffer) {
    buffer[pointer]=elem;
    return buffer;
}

bool ifFull (std::vector<int> List){
    int counter=0;
    for (elem : List){
        if (elem==-1){
            counter++;
        }
    }
    if (counter>0) {
        return false;
    } else {
        return true;
    }
}

int soFar (std::vector<int> page, std::vector<int> buffer, int pointer){
    int maxCounter = 0;
    int index=0;
    for (elem : buffer){
        int counter=0;
        for (pageElem : page) {
            if (elem==pageElem){
                break;
            }
            counter++;
        }
        if (counter>maxCounter){
            maxCounter=counter;
            pointer=index;
        }
        index++;
    }
    return pointer;
}

int findRecent (int elem, std::vector<int> buffer){
    int pointer=-1;
    for (int i=0;i<buffer.size();i++){
        if (buffer[i]==elem){
            pointer=i;
        }
    }
    return pointer;
}

int findLeastRecent (std::vector<int> temp, std::vector<int> buffer){
    int maxVal=0;
    int save;
    int counter=0;
    std::reverse(temp.begin(), temp.end());
    for (elem : buffer){
            counter=0;
        for (wew : temp){
            counter++;
            if (elem==wew){
                if (maxVal<counter){
                    maxVal=counter;
                    save=elem;
                }
                break;
            }
        }
    }
    int pointer=-1;
    for (int i=0;i<buffer.size();i++){
        if (buffer[i]==save){
            pointer=i;
        }
    }
    return pointer;
}

int findMostFreq (std::vector<int> temp, std::vector<int> buffer) {
    int maxCount=0;
    int counter;
    int save;
    for (elem : buffer) {
        counter=0;
        for (wew : temp) {
            if (elem==wew){
                counter++;
            }
        }
        if (maxCount<counter){
            maxCount=counter;
            save=elem;
        }
    }
    int pointer;
    counter=0;
    for (elem : buffer){
        if (elem==save){
            pointer=counter;
        }
        counter++;
    }
    return pointer;
}

int findLeastFreq (std::vector<int> temp, std::vector<int> buffer) {
    int maxCount=temp.size();
    int counter;
    int save;
    for (elem : buffer) {
        counter=0;
        for (wew : temp) {
            if (elem==wew){
                counter++;
            }
        }
        if (maxCount>counter){
            maxCount=counter;
            save=elem;
        }
    }
    int pointer;
    counter=0;
    for (elem : buffer){
        if (elem==save){
            pointer=counter;
        }
        counter++;
    }
    return pointer;
}

std::vector<int> page(PageRepAlgo algo, int frameBufferSize, std::vector<int> pageReference){
    // implementation here
    std::vector<int> output;
    std::vector<int> frameBuffer;
    int pointer=0;
    if ((int) algo==0){ ///may error pag yung katabi is not in the buffer
        std::cout<<"MRU"<<std::endl;
        printList(pageReference);
        frameBuffer=clearList(frameBufferSize);
        int lastUsed=-1;
        for (elem : pageReference){
            if (inBuffer(elem, frameBuffer)){
                output.push_back(0);
            } else {
                output.push_back(1);
                if (ifFull(frameBuffer)){
                    pointer=findRecent(lastUsed, frameBuffer);
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                } else {
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                    pointer++;
                }
            }
            lastUsed=elem;
        }
    }
    else if ((int)algo==1){
        std::cout<<"LRU"<<std::endl;
        printList(pageReference);
        frameBuffer=clearList(frameBufferSize);
        std::vector<int> temp;
        for (elem : pageReference){
            temp.push_back(elem);
            if (inBuffer(elem, frameBuffer)){
                output.push_back(0);
            } else {
                output.push_back(1);
                if (ifFull(frameBuffer)){
                    pointer=findLeastRecent(temp, frameBuffer);
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                } else {
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                    pointer++;
                }
            }
        }
    }
    else if ((int)algo==2){
        std::cout<<"MFU"<<std::endl;
        printList(pageReference);
        frameBuffer=clearList(frameBufferSize);
        std::vector<int> temp;
        for (elem : pageReference){
            temp.push_back(elem);
            if (inBuffer(elem, frameBuffer)){
                output.push_back(0);
            } else {
                output.push_back(1);
                if (ifFull(frameBuffer)){
                    std::sort(frameBuffer.begin(),frameBuffer.end());
                    pointer=findMostFreq(temp, frameBuffer);
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                } else {
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                    pointer++;
                }
            }
        }
    }
    else if ((int)algo==3){
        std::cout<<"LFU"<<std::endl;
        printList(pageReference);
        frameBuffer=clearList(frameBufferSize);
        std::vector<int> temp;
        for (elem : pageReference){
            temp.push_back(elem);
            if (inBuffer(elem, frameBuffer)){
                output.push_back(0);
            } else {
                output.push_back(1);
                if (ifFull(frameBuffer)){
                    std::sort(frameBuffer.begin(),frameBuffer.end());
                    pointer=findLeastFreq(temp, frameBuffer);
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                } else {
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                    pointer++;
                }
            }
        }
    }
    return output;
}

int main() {
    std::vector<int> pageReference = {7,0,1,2,0,3,4,2,1,0,1};
    int frameBufferSize = 3;

    std::vector<int> MRUoutput = page(PageRepAlgo::MRU, frameBufferSize, pageReference);
    printList(MRUoutput);

    std::vector<int> LRUoutput = page(PageRepAlgo::LRU, frameBufferSize, pageReference);
    printList(LRUoutput);

    std::vector<int> MFUoutput = page(PageRepAlgo::MFU, frameBufferSize, pageReference);
    printList(MFUoutput);

    std::vector<int> LFUoutput = page(PageRepAlgo::LFU, frameBufferSize, pageReference);
    printList(LFUoutput);
}

