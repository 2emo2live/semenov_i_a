#include <queuep/c_queuep.h>
#include <queuep/queuep.hpp>

#include <map>

class QueueManager {
public:
	QueueManager(const QueueManager& a) = delete;
	QueueManager(QueueManager&& a) = delete;
	QueueManager& operator=(const QueueManager& a) = delete;
	QueueManager& operator=(QueueManager&& a) = delete;

	static QueueManager& instance() {
		static QueueManager QM;
		return QM;
	}

	ErrorCode CreateQueue(QueueHandler* queue);
	ErrorCode CloneQueue(QueueHandler source, QueueHandler* queue);
	ErrorCode DestroyQueue(QueueHandler queue);
	ErrorCode Pop(QueueHandler queue);
	ErrorCode Push(QueueHandler queue, int32_t value);
	ErrorCode IsEmpty(QueueHandler queue, int32_t* result);
	ErrorCode Top(QueueHandler queue, int32_t* result);
	const char* WhatIs(ErrorCode err);
private:
	QueueManager() = default;
	~QueueManager() = default;

	std::map<QueueHandler, QueueP> queues;
};

extern "C" {
	ErrorCode CreateQueue(QueueHandler* queue) {
		return QueueManager::instance().CreateQueue(queue);
	};
	ErrorCode CloneQueue(QueueHandler source, QueueHandler* queue) {
		return QueueManager::instance().CloneQueue(source, queue);
	};
	ErrorCode DestroyQueue(QueueHandler queue) {
		return QueueManager::instance().DestroyQueue(queue);
	};
	ErrorCode Pop(QueueHandler queue) {
		return QueueManager::instance().Pop(queue);
	};
	ErrorCode Push(QueueHandler queue, int32_t value) {
		return QueueManager::instance().Push(queue, value);
	};
	ErrorCode IsEmpty(QueueHandler queue, int32_t* result) {
		return QueueManager::instance().IsEmpty(queue, result);
	};
	ErrorCode Top(QueueHandler queue, int32_t* result) {
		return QueueManager::instance().Top(queue, result);
	};
	const char* WhatIs(ErrorCode err) {
		return QueueManager::instance().WhatIs(err);
	};
}