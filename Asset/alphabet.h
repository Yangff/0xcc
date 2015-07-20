#pragma once
namespace _0xCC {
	namespace Asset {
		class alphabet {
		private:
			static const char* table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]\\{}|;',./:\"<>?";
		public:
			static const size_t Size = 96;
			static int GetCode(char ch){
				for (int i = 0; i < Size; i++)
					if (table[i] == ch)
						return i;
				return -1;
			}
			static char GetChar(int id){
				if (id >= 0 && id < Size)
					return table[id];
				return 0;
			}
		};
	};
};