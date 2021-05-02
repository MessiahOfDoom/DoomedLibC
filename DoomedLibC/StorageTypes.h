#ifndef DOOMED_STORAGE_HGUARD
	
	#define DOOMED_STORAGE_HGUARD
	
	#include "DoomedHeader.h"

	namespace dlc {

		template <typename T>
		class LLKnot {
		private:
			LLKnot* nxt;
		public:
			LLKnot<T>(T dataIn, LLKnot<T>* nextIn = nullptr) : data(dataIn), nxt(nextIn) {};
			LLKnot*& next() { return nxt; }
			T data;
			friend std::ostream& operator<<(std::ostream& stream, LLKnot<T> knot) {
				return stream << knot.data;
			}
		};

		template <typename T>
		class LinkedList {
		public:
			LinkedList<T>() : head(nullptr), tail(nullptr) {};
			unsigned int length() { return this->length(head); }
			void add(T data) {
				this->add(head, data);
			}
			T* at(unsigned int i) { return this->at(head, i); }
			void clear() { this->clear(this->head); }


			friend std::ostream& operator<<(std::ostream& stream, LinkedList& l) {
				l.printList(stream << '[', l.head);
				return stream << ']' << endl;
			}
		private:
			LLKnot<T>* head;
			LLKnot<T>* tail;
			unsigned int length(LLKnot<T>* anchor) {
				return anchor == nullptr ? 0 : 1 + length(anchor->next());
			}
			LLKnot<T>*& add(LLKnot<T>*& anchor, T data) {
				if (anchor == nullptr) {
					anchor = new LLKnot<T>(data, nullptr);
					tail = anchor;
				}
				else anchor->next() = add(anchor->next(), data);
				return anchor;
			}
			T* at(LLKnot<T>*& anchor, unsigned int i) {
				return anchor == nullptr ? nullptr : i == 0 ? &(anchor->data) : at(anchor->next(), i - 1);
			}

			void clear(LLKnot<T>*& knot) {
				if (knot == nullptr)return;
				clear(knot->next());
				delete knot;
				knot = nullptr;
			}

			void printList(std::ostream& stream, LLKnot<T>* knot) {
				if (knot == nullptr)return;
				std::string s = knot->next() != nullptr ? ", " : " ";
				printList(stream << *knot << s, knot->next());
			}

		};

	}
#endif