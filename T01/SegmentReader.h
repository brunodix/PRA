//
// Created by bruno on 26/04/15.
//

#ifndef T01_SEGMENTREADER_H
#define T01_SEGMENTREADER_H


#include "student.h"
#include "constants.h"

class SegmentReader {
    private:
        int readCount = 0;
        FILE *dataFile;
        FILE *indexFile;
        int (*compare)(void const *, void const *);
        int getAvaiableRegs() {
            if (readCount < REG_NUM) {
                int result;
                const int diff = REG_NUM - readCount;
                if (diff < REG_PAGE_SIZE) {
                    result = diff;
                } else {
                    result = REG_PAGE_SIZE;
                }
                readCount += result;
                return result;
            } else
                return 0;
        }
    public:

        SegmentReader(FILE *fData, FILE *fIndexFile, int (*comp)(void const *, void const *)) {
            dataFile = fData;
            indexFile = fIndexFile;
            compare = comp;
        }

        Student* readSegment() {
            int regs = getAvaiableRegs();
            if (regs > 0) {
                long index[regs];
                for (int i = 0; i < regs; i++) {
                    index[i] = getNextIndex();
                }
                Student **elements = readElements(index, regs);
                qsort(elements, REG_PAGE_SIZE, STUDENT_SIZE, compare);
                return (Student *) elements;
            } else {
                return NULL;
            }
        }

        Student **readElements(long index[], int size) {
            Student **students = (Student **) new Student[size];
            for (int i = 0; i < size; i++) {
                students[i] = readElement(index[i]);
            }
            return students;
        }

        Student *readElement(int index) {
            fseek(dataFile, (index * STUDENT_SIZE), SEEK_SET);
            Student *student = new Student();
            fread(student, STUDENT_SIZE, 1, dataFile);
            return student;
        }

        int getNextIndex() {
            long result;
            fread(&result, LONG_SIZE, 1, indexFile);
            fseek(indexFile, INDEX_OFFSET, SEEK_CUR);
            cout << "NExt Index:" << result << " pos:" << ftell(indexFile) << endl;
            return result;
        }

};


#endif //T01_SEGMENTREADER_H
