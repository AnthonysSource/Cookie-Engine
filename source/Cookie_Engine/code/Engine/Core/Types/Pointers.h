#pragma once

#include <memory>

namespace Cookie {

	template <typename T> using Ref = std::shared_ptr<T>;
	template <typename T> using WeakRef = std::weak_ptr<T>;

} // namespace Cookie