// bridge.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>

typedef int ThreadID;
typedef int Privilege;
typedef int TimeSlice;

//Implementer
class ThreadScheduleImplementer {
public:
    virtual void Schedule(ThreadID thread) = 0;
    virtual Privilege GetThreadPrivilege(ThreadID thread) {
        return 0;
    }
    virtual TimeSlice GetThreadTimeSlice(ThreadID thread) {
        return 0;
    }
};

//Abstraction
class ThreadScheduler {
public:
    ThreadScheduler(ThreadScheduleImplementer* implementer) {
        implementer_ = implementer;
    }

    virtual void Schedule(const std::vector<ThreadID>& threads) = 0;

protected:
    ThreadScheduleImplementer * implementer_ = nullptr;
};

//Refined Abstraction 1 �� ��ռʽ�̵߳���
class PreemptiveThreadScheduler : public ThreadScheduler {
public:
    PreemptiveThreadScheduler(ThreadScheduleImplementer* implementer) : ThreadScheduler(implementer) {
        
    }

    void Schedule(const std::vector<ThreadID>& threads) override {
        if (threads.empty()) {
            return;
        }

        auto greater_privilege = [this](ThreadID id1, ThreadID id2) -> bool {
            return (this->GetThreadPrivilege(id1) > this->GetThreadPrivilege(id2));
        };
        std::vector<ThreadID> threads_copy(threads);
        std::sort(threads_copy.begin(), threads_copy.end(), greater_privilege);
        ThreadID thread = threads_copy.front();
        implementer_->Schedule(thread);

        std::cout << "thread:" << thread << " Scheduled by Preemptive strategy." << std::endl;
    }

    Privilege GetThreadPrivilege(ThreadID thread) {
        return implementer_->GetThreadPrivilege(thread);
    }
};

//Refined Abstraction 2 �� ʱ��Ƭʽ�̵߳���
class TimeSliceThreadScheduler : public ThreadScheduler {
public:
    TimeSliceThreadScheduler(ThreadScheduleImplementer* implementer) : ThreadScheduler(implementer) {

    }

    void Schedule(const std::vector<ThreadID>& threads) override {
        if (threads.empty()) {
            return;
        }

        auto greater_timeslice = [this](ThreadID id1, ThreadID id2) -> bool {
            return (this->GetThreadTimeSlice(id1) > this->GetThreadTimeSlice(id2));
        };
        std::vector<ThreadID> threads_copy(threads);
        std::sort(threads_copy.begin(), threads_copy.end(), greater_timeslice);
        ThreadID thread = threads_copy.back();
        implementer_->Schedule(thread);

        std::cout << "thread:"<< thread << " Scheduled by TimeSlice strategy." << std::endl;
    }

    TimeSlice GetThreadTimeSlice(ThreadID thread) {
        return implementer_->GetThreadTimeSlice(thread);
    }
};

//Concrete Implementer 1 : Windows Implementation
class WindowsThreadScheduleImplementer : public ThreadScheduleImplementer {
public:
    void Schedule(ThreadID thread) override {
        std::cout << "Scheduling thread:" << thread << " on Windows." << std::endl;
    }

    Privilege GetThreadPrivilege(ThreadID thread) override {
        return 0;
    }
    
    TimeSlice GetThreadTimeSlice(ThreadID thread) override {
        return 0;
    }
};

//Concrete Implementer 2 : Linux Implementation
class LinuxThreadScheduleImplementer : public ThreadScheduleImplementer {
public:
    void Schedule(ThreadID thread) override {
        std::cout << "Scheduling thread:" << thread << " on Linux." << std::endl;
    }

    Privilege GetThreadPrivilege(ThreadID thread) override {
        return 0;
    }

    TimeSlice GetThreadTimeSlice(ThreadID thread) override {
        return 0;
    }
};

/*
    Bridgeģʽ����������������仯�����أ����Ȳ�����ƽ̨��
    ���Ҽ�����ϵͳ�����������
    ����ʵ��LinuxPreemtiveThreadScheduleImplementer, LinuxTimeSliceThreadScheduleImplementer,
           WindowsPreemtiveThreadScheduleImplementer, WindowsTimeSliceThreadScheduleImplementer��
    ����и�����ԣ�����ƽ̨��������ݾͻἱ��������
*/

int main()
{
    std::vector<ThreadID> threads;
    threads.push_back(1);
    threads.push_back(2);
    threads.push_back(3);

    //����ƽ̨ʵ��
    WindowsThreadScheduleImplementer* windows_implementer = new WindowsThreadScheduleImplementer();
    LinuxThreadScheduleImplementer* linux_implementer = new LinuxThreadScheduleImplementer();

    //����ƽ̨�����ֵ��Ȳ���
    ThreadScheduler* windows_pt_scheduler = new PreemptiveThreadScheduler(windows_implementer);
    ThreadScheduler* linux_pt_scheduler = new PreemptiveThreadScheduler(linux_implementer);
    ThreadScheduler* windows_ts_scheduler = new TimeSliceThreadScheduler(windows_implementer);
    ThreadScheduler* linux_ts_scheduler = new TimeSliceThreadScheduler(linux_implementer);

    //�̵߳���
    windows_pt_scheduler->Schedule(threads);
    linux_pt_scheduler->Schedule(threads);
    windows_ts_scheduler->Schedule(threads);
    linux_ts_scheduler->Schedule(threads);

    delete windows_pt_scheduler;
    delete linux_pt_scheduler;
    delete windows_ts_scheduler;
    delete linux_ts_scheduler;
    delete windows_implementer;
    delete linux_implementer;

    return 0;
}

