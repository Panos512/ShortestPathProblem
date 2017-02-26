//
// Created by Panos Paparrigopoulos on 12/01/2017.
//

#include <pthread.h>

#include "JobQueue.hpp"
#include "Grails.h"
#include "scc.hpp"
#include "bfs.hpp"
#include "Index.hpp"
#include "cc.hpp"


class JobScheduler {
private:
    int execution_threads, k; // number of execution threads
    int jobNo, jobsExecuted, jobsOnArray;
    int* results;
    JobQueue* queue;  // a queue that holds submitted jobs / tasks
    pthread_t* tids; // Threads
    pthread_cond_t jobs_created, cond, mainCond;
    pthread_mutex_t array_mutex , mtx, mainMtx, fEnd;

    bool readingQueries, jobExecution;

    Grails* grails;
    SCC* scc;
    BFS* bfs;
    Index* indexInternal;
    Index* indexExternal;
    CC* cc;
    bool dynamic;

public:
    JobScheduler(int execution_threads);

    virtual ~JobScheduler();

    int getExecution_threads() const;
    void setExecution_threads(int execution_threads);

    void pushJob(Job* job);
    Job* popJob();

    static void* runJob(void*);

    bool queueIsEmpty();

    void printQueue();

    void updateReadingQueries(bool);

    void wakeUpThreads(Grails*, SCC*, BFS*, Index*, Index*, CC*, bool);

    void executeJob(Job*);

    void printResults();

    void allocArray(int jobs);

    void work();

    void waitMainThread();

    void updateFinished(bool);

    void waitForAll();

    Grails *getGrails() const;

    void setGrails(Grails *grails);

    SCC *getScc() const;

    void setScc(SCC *scc);

    BFS *getBfs() const;

    void setBfs(BFS *bfs);

    Index *getIndexInternal() const;

    void setIndexInternal(Index *indexInternal);

    Index *getIndexExternal() const;

    void setIndexExternal(Index *indexExternal);

    CC *getCc() const;

    void setCc(CC *cc);

    bool isDynamic() const;

    void setDynamic(bool dynamic);
};


