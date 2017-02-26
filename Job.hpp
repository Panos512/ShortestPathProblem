//
// Created by Panos Paparrigopoulos on 12/01/2017.
//

#ifndef SHORTESTPATHPROBLEM_SOFTDEV2017_JOB_HPP
#define SHORTESTPATHPROBLEM_SOFTDEV2017_JOB_HPP


#include <cstdint>

class Job {

private:
    char type;
    int version;
    int jobNumber;
    int jobBurstNumber;
    uint32_t nodeFrom;
    uint32_t nodeTo;

public:
    int getJobBurstNumber() const;

    void setJobBurstNumber(int jobBurstNumber);

    char getType() const;

    void setType(char type);

    int getVersion() const;

    void setVersion(int version);

    uint32_t getNodeFrom() const;

    void setNodeFrom(uint32_t nodeFrom);

    uint32_t getNodeTo() const;

    void setNodeTo(uint32_t nodeTo);

    int getJobNumber() const;

    void setJobNumber(int jobNumber);

};


#endif //SHORTESTPATHPROBLEM_SOFTDEV2017_JOB_HPP
