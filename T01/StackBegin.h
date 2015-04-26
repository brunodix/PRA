#ifndef PRA_T01_STACK_H
#define PRA_T01_STACK_H


class StackBegin {
        Student *elements;
        Student *selected;
        long counter;
        long limit;
    public:
        Student *getSelected();
        void stepNext();

    void setElements(Student *pStudent, int arraySize);
};


#endif //PRA_T01_STACK_H

Student * StackBegin::getSelected() {
    if (selected == NULL) {
        stepNext();
    }
    return selected;
}


void StackBegin::stepNext() {
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
