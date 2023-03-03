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
        // TODO: replace this code with a faster algorithm.
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        vector<long long> next_free_time(num_workers_, 0);
        for (int i = 0; i < jobs_.size(); i++) {
            int duration = jobs_[i];
            int next_worker = 0;
            for (int j = 0; j < num_workers_; ++j) {
                if (next_free_time[j] < next_free_time[next_worker])
                    next_worker = j;
            }
            assigned_workers_[i] = next_worker;
            start_times_[i] = next_free_time[next_worker];
            next_free_time[next_worker] += duration;
        }
    }

    void AssignJobsFast(){
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        vector<long long> next_free_time(num_workers_, 0);
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for (auto i : jobs_){
            pq.push(i);
        }
        int count=0;
        while (!pq.empty()){
            long long duration = pq.top();
            pq.pop();
            int next_worker = 0;
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
        AssignJobsFast();
        WriteResponse();
    }
};
int main()
{
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}