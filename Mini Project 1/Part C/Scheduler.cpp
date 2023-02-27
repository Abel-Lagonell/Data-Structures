#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class JobQueue
{
private:
    int num_workers_;
    vector<int> jobs_;
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
    
    //Using Priority Queue to assign jobs to workers
    void AssignJobs(){
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        //Pushing the workers into the priority queue
        for (int i = 0; i < num_workers_; i++) {
            pq.push({0, i});
        }
        //Assigning jobs to workers
        for (int i = 0; i < jobs_.size(); i++) {
            pair<int, int> top = pq.top();
            pq.pop();
            assigned_workers_[i] = top.second;
            start_times_[i] = top.first;
            pq.push({top.first + jobs_[i], top.second});
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