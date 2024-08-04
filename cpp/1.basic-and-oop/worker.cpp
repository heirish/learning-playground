#include "worker.h"

int Worker::m_count{0};
Worker::Worker(std::string_view job) : m_job(job) {m_count++;}
Worker::Worker(std::string_view job, int age) : m_job(job) {
    m_age = age;
    //m_address = "dd"; //error:Person::m_address is not accessable.
    m_count++;
}
Worker::Worker(std::string_view name, int age, std::string_view address, std::string_view job):Person(name, age, address), m_job(job)
{
    m_count++;

}
Worker::Worker(const Worker &rhs):Person(rhs), m_job(rhs.m_job) {m_count++;}

std::ostream& operator<<(std::ostream &os, const Worker& worker)
{
    os << "Worker name:" << worker.get_name()<< ",age:" << worker.get_age()<< ",address:" << worker.get_address() << ",job:" << worker.m_job;
    return os;
}