//
// Created by Panos Paparrigopoulos on 12/01/2017.
//

#include "JobScheduler.hpp"
#include "Grails.h"
#include "scc.hpp"
#include "bfs.hpp"
#include "Index.hpp"
#include "cc.hpp"

bool _fCloseThreads;

JobScheduler::JobScheduler(int execution_threads){
    pthread_cond_init(&jobs_created, NULL);
    pthread_mutex_init(&array_mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&mainCond, NULL);
    pthread_mutex_init(&mainMtx, NULL);
    pthread_mutex_init(&fEnd, NULL);
    k = 0;
    jobNo = 0;
    jobsExecuted = 0;
    jobsOnArray = 0;
    readingQueries = true;
    jobExecution = true;
    this->execution_threads = execution_threads;
    _fCloseThreads = false;
    this->queue = new JobQueue();

    tids = (pthread_t*) malloc(sizeof(pthread_t)*execution_threads);
    for(int i = 0; i < execution_threads; i++)
    {
        pthread_create(&tids[i], NULL, JobScheduler::runJob, this);
    }

}


void* JobScheduler::runJob(void* schedulerPtr){
    JobScheduler* scheduler = (JobScheduler*) schedulerPtr;
    //cout << "Thread started" << endl;
    while(!_fCloseThreads) {
        pthread_mutex_lock(&scheduler->array_mutex);
        while (scheduler->readingQueries) {
            pthread_cond_wait(&scheduler->jobs_created, &scheduler->array_mutex);
        }

        pthread_mutex_unlock(&scheduler->array_mutex);
        scheduler->work();
    }


    pthread_exit(NULL);

}


int JobScheduler::getExecution_threads() const {
    return execution_threads;
}

void JobScheduler::setExecution_threads(int execution_threads) {
    JobScheduler::execution_threads = execution_threads;
}

void JobScheduler::pushJob(Job *job) {
    jobNo++;
    queue->pushBack(job);
}

Job* JobScheduler::popJob() {
    return queue->popFront();
}


bool JobScheduler::queueIsEmpty() {
    return queue->isEmpty();
}


void JobScheduler::printQueue() {
    queue->print();
}

JobScheduler::~JobScheduler() {
    free(tids);
}

void JobScheduler::updateReadingQueries(bool newVal){
    readingQueries = newVal;
}

void JobScheduler::executeJob(Job* job){
    if(!dynamic){

        if (grails->isReachableGrailIndex(scc->id_belongs_to_component[job->getNodeFrom()],
                                          scc->id_belongs_to_component[job->getNodeTo()])) {
            results[job->getJobBurstNumber()] = bfs->findShortestPath(indexInternal, indexExternal, job->getNodeFrom(), job->getNodeTo(), job->getJobNumber(), 0);
        } else {
            results[job->getJobBurstNumber()] = -1;
        }
    }else{

        if(cc->sameComponent(job->getNodeFrom(), job->getNodeTo())){
            results[job->getJobBurstNumber()] = bfs->findShortestPath(indexInternal, indexExternal, job->getNodeFrom(), job->getNodeTo(), job->getJobNumber(), job->getVersion());
        }else
            results[job->getJobBurstNumber()] = -1;
    }
}

void JobScheduler::printResults(){
        for(int i=0; i<jobsOnArray; i++){
            cout << results[i] << endl;
        }
        jobsOnArray = 0;
   delete[] results;
}

void JobScheduler::allocArray(int jobs) {
    this->results = new int[jobs];
}



void JobScheduler::wakeUpThreads(Grails* grails, SCC* scc, BFS* bfs, Index* indexInternal, Index* indexExternal, CC* cc, bool dynamic){
    pthread_mutex_lock (&mainMtx);

    this->setGrails(grails);
    this->setScc(scc);
    this->setBfs(bfs);
    this->setIndexInternal(indexInternal);
    this->setIndexExternal(indexExternal);
    this->setCc(cc);
    this->setDynamic(dynamic);


    updateReadingQueries(false);
    jobExecution = true;
    pthread_mutex_unlock (&mainMtx);

    pthread_cond_broadcast(&jobs_created);

}

void JobScheduler::work(){
    while(!this->queueIsEmpty()){
        pthread_mutex_lock(&array_mutex);

        if(!this->queueIsEmpty()){
            Job* job = this->popJob();
            this->executeJob(job);
            jobsExecuted++;
            jobsOnArray++;
            free(job);
        }
        pthread_mutex_unlock(&array_mutex);


    }
    pthread_mutex_lock(&array_mutex);
    k++;
    if(jobNo == jobsExecuted && jobNo != 0) {
        pthread_mutex_lock(&mainMtx);

        jobExecution = false;
        pthread_mutex_unlock(&mainMtx);

        jobNo = 0;
        jobsExecuted = 0;
        updateReadingQueries(true);

        pthread_cond_signal(&mainCond);
    }
    pthread_mutex_unlock(&array_mutex);

}

void JobScheduler::waitMainThread(){
    pthread_mutex_lock(&mainMtx);
    while(jobExecution){
        pthread_cond_wait(&mainCond,  &mainMtx);
    }
    pthread_mutex_unlock(&mainMtx);
}

void JobScheduler::updateFinished(bool value){
    _fCloseThreads = value;
}

void JobScheduler::waitForAll(){
    pthread_cond_broadcast(&jobs_created);
    for(int i = 0; i < execution_threads; i++){
        pthread_join(tids[i], NULL);
    }
}

Grails *JobScheduler::getGrails() const {
    return grails;
}

void JobScheduler::setGrails(Grails *grails) {
    JobScheduler::grails = grails;
}

SCC *JobScheduler::getScc() const {
    return scc;
}

void JobScheduler::setScc(SCC *scc) {
    JobScheduler::scc = scc;
}

BFS *JobScheduler::getBfs() const {
    return bfs;
}

void JobScheduler::setBfs(BFS *bfs) {
    JobScheduler::bfs = bfs;
}

Index *JobScheduler::getIndexInternal() const {
    return indexInternal;
}

void JobScheduler::setIndexInternal(Index *indexInternal) {
    JobScheduler::indexInternal = indexInternal;
}

Index *JobScheduler::getIndexExternal() const {
    return indexExternal;
}

void JobScheduler::setIndexExternal(Index *indexExternal) {
    JobScheduler::indexExternal = indexExternal;
}

CC *JobScheduler::getCc() const {
    return cc;
}

void JobScheduler::setCc(CC *cc) {
    JobScheduler::cc = cc;
}

bool JobScheduler::isDynamic() const {
    return dynamic;
}

void JobScheduler::setDynamic(bool dynamic) {
    JobScheduler::dynamic = dynamic;
}
