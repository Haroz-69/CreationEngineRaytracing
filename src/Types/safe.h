#pragma once

#include "PCH.h"

namespace safe
{
	template <typename T>
	class vector {
		eastl::vector<T> m_Vector;
		std::shared_mutex m_Mutex;

	public:
		bool empty() const {
			std::shared_lock lock(m_Mutex);
			return m_Vector.empty();
		}

		void push_back(T item) {
			std::unique_lock lock(m_Mutex);
			m_Vector.push_back(item);
		}

		template<class... Args>
		auto& emplace_back(Args&&... args) {
			std::unique_lock lock(m_Mutex);
			return m_Vector.emplace_back(eastl::forward<Args>(args)...);
		}
	};
}