#ifndef DOOMED_MATRIX_HGUARD

	#define DOOMED_MATRIX_HGUARD

	#include "DoomedHeader.h"
	#include <vector>

namespace dlc {
	class Matrix {
	private:
		std::vector<std::vector<C80>> nums;
		UINT32 m, n;
	public:
		Matrix(UINT32 m_in, UINT32 n_in) : m(m_in), n(n_in) {
			nums.resize(m);
			for (int i = 0; i < m; i++) {
				std::vector<C80> row;
				row.resize(n);
				nums[i] = row;
			}
		};

		Matrix(const Matrix& other): m(other.m), n(other.n) {
			nums.resize(m);
			for (int i = 0; i < m; i++) {
				std::vector<C80> row;
				row.resize(n);
				for (int j = 0; j < n; j++) {
					row[j] = other[i][j];
				}
				nums[i] = row;
			}
		}

		~Matrix() {
			std::vector<std::vector<C80>>().swap(nums);
		}

		std::vector<C80>& operator[](std::size_t idx) {
			return nums[idx];
		}

		const std::vector<C80>& operator[](std::size_t idx) const {
			return nums[idx];
		}

		Matrix& operator*=(const C80& c) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					nums[i][j] *= c;
				}
			}
			return *this;
		}

		Matrix operator*(const C80& c) {
			Matrix out = { m, n };
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					out[i][j] = nums[i][j] * c;
				}
			}
			return out;
		}

		Matrix operator*(Matrix& other) {
			
			if (other.m != n)throw new incompatible_dimensions();
			Matrix out = { m, other.n };
			for (int i = 0; i < out.m; i++) {
				for (int j = 0; j < out.n; j++) {
					C80 val;
					for (int k = 0; k < n; k++) {
						val += nums[i][k] * other[k][j];
					}
					out[i][j] = val;
				}
			}
			return out;
		}

		Matrix& operator=(const Matrix& other) {
			std::vector<std::vector<C80>>().swap(nums);
			this->m = other.m;
			this->n = other.n;
			nums.resize(m);
			for (int i = 0; i < m; i++) {
				std::vector<C80> row;
				row.resize(n);
				for (int j = 0; j < n; j++) {
					row[j] = other[i][j];
				}
				nums[i] = row;
			}
			return *this;
		}

		Matrix operator+(Matrix& other) {

			if (other.m != m || other.n != n)throw new incompatible_dimensions();
			Matrix out = { m, n };
			for (int i = 0; i < out.m; i++) {
				for (int j = 0; j < out.n; j++) {
					out[i][j] = nums[i][j] + other[i][j];
				}
			}
			return out;
		}

		Matrix transpose() {
			Matrix out = { n, m };
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					out[j][i] = nums[i][j];
				}
			}
			return out;
		}

		friend std::ostream& operator<<(std::ostream&, const Matrix&);
	};
	
	class Vector : public Matrix {
	public:
		Vector(int n_in) : Matrix(1, n_in) {};
	};

	std::ostream& operator<<(std::ostream& s, const Matrix& m) {
		s << "[\n";
		for (int i = 0; i < m.m; i++) {
			for (int j = 0; j < m.n; j++) {
				s << m[i][j] << (j + 1 < m.n ? ", " : "");
			}
			s << "\n";
		}
		return s << "]" << endl;
	}
}

	


#endif