#pragma once
#include <array>
#include <vector>
#include <type_traits>

namespace rectpack {
	template <bool allow_flip>
	using output_rect = std::conditional_t<allow_flip, rect_xywhf, rect_xywh>;

	class default_empty_spaces {
		std::vector<rect_ltrb> empty_spaces;

	protected:
		void delete_empty_space(const int i) {
			empty_spaces[i] = empty_spaces.back();
			empty_spaces.pop_back();
		}

		bool add_empty_space(const rect_ltrb r) {
			empty_spaces.emplace_back(r);
			return true;
		}

		auto get_count_empty_spaces() const {
			return empty_spaces.size();
		}

		void reset() {
			empty_spaces.clear();
		}

		const auto& get_empty_space(const int i) {
			return empty_spaces[i];
		}
	};

	template <int MAX_SPACES>
	class static_empty_spaces {
		std::array<rect_ltrb, MAX_SPACES> empty_spaces;
		int count_spaces = 0;

	protected:
		void delete_empty_space(const int i) {
			empty_spaces[i] = empty_spaces[count_spaces - 1];
			--count_spaces;
		}

		bool add_empty_space(const rect_ltrb r) {
			if (count_spaces < empty_spaces.size()) {
				empty_spaces[count_spaces] = r;
				++count_spaces;

				return true;
			}

			return false;
		}
		
		auto get_count_empty_spaces() const {
			return count_spaces;
		}

		void reset() {
			count_spaces = 0;
		}

		const auto& get_empty_space(const int i) {
			return empty_spaces[i];
		}
	};
}