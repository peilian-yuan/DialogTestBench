#pragma once
#include <map>
#include <string>
#include <mutex>

#ifdef _DEBUG
//#define RSC_TRACKER
//#define RAII // Resource Acquisition Is Initialization
#ifdef RSC_TRACKER
#define TRACK_RESOURCE(type, ptr) ResourceTracker::Track(type, ptr, __FILE__, __LINE__)
#define UNTRACK_RESOURCE(type, ptr) ResourceTracker::Untrack(type, ptr)
#else
#define TRACK_RESOURCE(type, ptr)
#define UNTRACK_RESOURCE(type, ptr)
#endif
#endif

class ResourceTracker {
public:
    static void Track(const char* type, void* ptr, const char* file, int line);
    static void Untrack(const char* type, void* ptr);
    static void ReportLeaks();

private:
    struct AllocationInfo {
        const char* type;
        const char* file;
        int line;
    };

    static std::map<void*, AllocationInfo> allocations;
    static std::mutex mutex;
};

// Custom deleter that also untracks resources
template<typename T>
struct TrackingDeleter {
    void operator()(T* ptr) const {
        UNTRACK_RESOURCE(typeid(T).name(), ptr);
        delete ptr;
    }
};

// Helper function to create tracked unique_ptr
template<typename T, typename... Args>
std::unique_ptr<T, TrackingDeleter<T>> make_tracked_unique(Args&&... args) {
    auto ptr = new T(std::forward<Args>(args)...);
    TRACK_RESOURCE(typeid(T).name(), ptr);
    return std::unique_ptr<T, TrackingDeleter<T>>(ptr);
}