/**
 * @file Scheduler.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class JobQueue
{
private:
    int num_workers_;
    vector<long long> jobs_;
    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const{
        for (int i = 0; i < jobs_.size(); ++i){
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }
    void ReadData(){
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for (int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }
    

    void AssignJobs(){
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        vector<long long> next_free_time(num_workers_, 0);
        //Set up priority queue
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        //Fill priority queue with jobs
        for (auto i : jobs_){
            pq.push(i);
        }
        int count=0;
        while (!pq.empty()){
            long long duration = pq.top();
            pq.pop();
            int next_worker = 0;
            //Find next worker to assign job to
            for (int j = 0; j < num_workers_; j++) {
                if (next_free_time[j] < next_free_time[next_worker])
                    next_worker = j;
            }
            assigned_workers_[count] = next_worker;
            start_times_[count] = next_free_time[next_worker];
            next_free_time[next_worker] += duration;
            count++;
        }
    }



public:
    void Solve()
    {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};
int main()
{
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}