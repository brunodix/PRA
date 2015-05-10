#include "SegmentReader.h"

#ifndef PRA_T01_STACK_H
#define PRA_T01_STACK_H


class StackBegin {
        SegmentReader *segmentReader;
        Student *elements = NULL;
        Student *selected = NULL;
        long counter;
        long limit;
    public:
        Student *getSelected();
        void stepNext();

    void setElements(Student *pStudent, int arraySize);
    void setSegmentReader(SegmentReader *segReader);
    void getCurrentIndex();
};

#endif //PRA_T01_STACK_H

Student * StackBegin::getSelected() {
    if (selected == NULL) {
        stepNext();
    }
    return selected;
}


void StackBegin::stepNext() {
    if (elements == NULL) {
        elements = segmentReader->readSegment();
    }
    if (counter < limit) {
        selected = &elements[counter++];
    } else {
        selected = NULL;
    }
}

void StackBegin::setElements(Student *pStudent, int arraySize) {
    elements = pStudent;
    counter = 0;
    limit = arraySize-1;
    stepNext();
}

void StackBegin::setSegmentReader(SegmentReader *segReader) {
    segmentReader = segReader;
}
