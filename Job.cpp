//
// Created by Panos Paparrigopoulos on 12/01/2017.
//

#include "Job.hpp"

char Job::getType() const {
    return type;
}

void Job::setType(char type) {
    Job::type = type;
}

int Job::getVersion() const {
    return version;
}

void Job::setVersion(int version) {
    Job::version = version;
}

uint32_t Job::getNodeFrom() const {
    return nodeFrom;
}

void Job::setNodeFrom(uint32_t nodeFrom) {
    Job::nodeFrom = nodeFrom;
}

uint32_t Job::getNodeTo() const {
    return nodeTo;
}

void Job::setNodeTo(uint32_t nodeTo) {
    Job::nodeTo = nodeTo;
}

int Job::getJobNumber() const {
    return jobNumber;
}

void Job::setJobNumber(int jobNumber) {
    Job::jobNumber = jobNumber;
}

int Job::getJobBurstNumber() const {
    return jobBurstNumber;
}

void Job::setJobBurstNumber(int jobBurstNumber) {
    Job::jobBurstNumber = jobBurstNumber;
}
