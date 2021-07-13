#include <iostream>
#include <string>
#include <math.h>
using namespace std;
struct pos {
	int i, j;
};
struct dual {
	string bin;
	char hex;
};
template <class arr_type> class matrix {
	int n_col, n_row;
	int row_now, col_now;
	arr_type **arr;
public:
	matrix(int n, int m, arr_type* input_arr = NULL) :n_row(n), n_col(m), row_now(0), col_now(0) {
		arr = new arr_type*[n];
		arr_type *temp_arr;
		if (input_arr == NULL) {
			temp_arr = new arr_type[1];
			temp_arr[0] = 0;
		}
		else {
			temp_arr = input_arr;
			row_now = n; col_now = m;
		}
		int count = 0;
		for (int i = 0; i < n; i++) {
			arr[i] = new arr_type[m];
			for (int j = 0; j < m; j++) {
				arr[i][j] = temp_arr[count++];
				if (input_arr == NULL) {
					count--;
				}
			}
		}
	}
	arr_type& operator()(int i, int j) {
		return arr[i][j];
	}
	arr_type **get() {
		return arr;
	}
	int get_ncol() {
		return n_col;
	}
	int get_nrow() {
		return n_row;
	}
	bool add_match(matrix a) {
		if (a.get_ncol() == get_ncol() && a.get_nrow() == get_nrow()) {
			return 1;
		}
		return 0;
	}
	matrix operator+ (matrix a) {
		if (add_match(a)) {
			matrix <arr_type> result(n_row, n_col);
			for (int i = 0; i < n_row; i++) {
				for (int j = 0; j < n_col; j++) {
					result(i, j) = a(i, j) + arr[i][j];
				}
			}
			return result;
		}
		else {
			return matrix <arr_type>(NULL, NULL);
		}
	}
	template <class mulop> matrix operator*(mulop a) { //accepts float operations if the original matrix is of float type
		matrix <arr_type> temp(n_row, n_col);
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				temp(i, j) = arr[i][j] * a;
			}
		}
		return temp;
	}
	matrix operator% (int a) {
		matrix <arr_type> temp(n_row, n_col);
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				temp(i, j) = arr[i][j] % a;
			}
		}
		return temp;
	}
	void print() {
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	bool mul_match(matrix a) {
		if (n_col == a.get_nrow()) {
			return 1;
		}
		else {
			return 0;
		}
	}
	matrix operator*(matrix a) {
		if (mul_match(a)) {
			matrix <arr_type> result(n_row, a.get_ncol());
			for (int i = 0; i < n_row; i++) {
				for (int j = 0; j < a.get_ncol(); j++) {
					for (int t = 0; t < n_col; t++) {
						result(i, j) += arr[i][t] * a(t, j);
					}
				}
			}
			return result;
		}
		else {
			return matrix<arr_type>(NULL, NULL);
		}
	}
	matrix transpose() {
		matrix <arr_type> result(n_col, n_row);
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				result(j, i) = arr[i][j];
			}
		}
		return result;
	}
	bool exists(arr_type ele) {
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				if (arr[i][j] == ele) {
					return 1;
				}
			}
		}
		return 0;
	}
	void append(arr_type ele) {
		if (col_now >= n_col) {
			col_now = 0;
			row_now++;
		}
		if (row_now >= n_row) {
			cout << "NO" << endl;
		}
		else {
			arr[row_now][col_now++] = ele;
		}
	}
	pos index(arr_type ele) {
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				if (ele == arr[i][j]) {
					return pos({ i, j });
				}
			}
		}
		return pos({ -1, -1 });
	}
};
dual binhexarr[16] = {
	{ "0000" , '0' } ,{ "0001" , '1' },{ "0010" , '2' },{ "0011" , '3' },
	{ "0100" , '4' },{ "0101" , '5' },{ "0110" , '6' },{ "0111" , '7' },{ "1000",'8' } ,
	{ "1001",'9' },{ "1010",'A' },{ "1011",'B' },{ "1100",'C' },{ "1101",'D' },
	{ "1110",'E' },{ "1111",'F' }
};
string hex_to_bin(string hexa_str) {
	string BIN = "";
	for (int i = 0; i < hexa_str.length(); i++) {
		for (int j = 0; j < 16; j++) {
			if (hexa_str[i] == binhexarr[j].hex) {
				BIN += binhexarr[j].bin;
				break;
			}
		}
	}
	return BIN;
}
string bin_to_hex(string bin_str) {
	string HEXA = "";
	for (int i = 0; i < bin_str.length(); i += 4) {
		for (int j = 0; j < 16; j++) {
			if (bin_str.substr(i, 4) == binhexarr[j].bin) {
				HEXA += binhexarr[j].hex;
				break;
			}
		}
	}
	return HEXA;
}
string PC_1(string orgkeyHEXA) {
	int arr[56] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27
		,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22
		,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
	string bin_key = hex_to_bin(orgkeyHEXA);
	string permutated_bin = "";
	for (int i = 0; i < 56; i++) {
		arr[i] -= 1;
		permutated_bin += bin_key[arr[i]];
	}
	return bin_to_hex(permutated_bin);
}
string cir(string strHEXA) {
	string str = hex_to_bin(strHEXA);
	string left = "", right = "";
	left = str.substr(1, (str.length() / 2) - 1);
	right = str.substr((str.length() / 2) + 1, (str.length() / 2) - 1);
	right += str[str.length() / 2];
	left += str[0];
	return bin_to_hex(left + right);
}
string PC_2(string strHEXA) {
	string strBIN = hex_to_bin(strHEXA);
	int arr[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8
		,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,
		44,49,39,56,34,53,46,42,50,36,29,32 };
	string permutated_bin = "";
	for (int i = 0; i < 48; i++) {
		arr[i] -= 1;
		permutated_bin += strBIN[arr[i]];
	}
	return bin_to_hex(permutated_bin);
}
string IP(string strHEX) {
	int arr[64] = { 58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7 };
	string permutated_str = "";
	string strBIN = hex_to_bin(strHEX);
	for (int i = 0; i < 64; i++) {
		arr[i] -= 1;
		permutated_str += strBIN[arr[i]];
	}
	return bin_to_hex(permutated_str);
}
string E(string strHEX) {
	string strBIN = hex_to_bin(strHEX);
	int arr[48] = { 32,1,2,3,4,5,
		4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,
		24,25,26,27,28,29,28,29,30,31,32,1 };
	string after_exp = "";
	for (int i = 0; i < 48; i++) {
		arr[i] -= 1;
		after_exp += strBIN[arr[i]];
	}
	return bin_to_hex(after_exp);
}
string xor (string HEX_1, string HEX_2) {
	string BIN_1 = hex_to_bin(HEX_1), BIN_2 = hex_to_bin(HEX_2);
	string resultBIN = "";
	for (int i = 0; i < BIN_1.length(); i++) {
		resultBIN += ((BIN_1[i] ^ BIN_2[i]) + int('0'));
	}
	return bin_to_hex(resultBIN);
}
int s1[4][16] = {
	{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
	{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
	{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
	{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
};
int s2[4][16] = {
	{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
	{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
	{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
	{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
};
int s3[4][16] = {
	{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
	{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
	{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
	{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
};
int s4[4][16] = {
	{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
	{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
	{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
	{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
};
int s5[4][16] = {
	{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
	{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
	{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
	{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
};
int s6[4][16] = {
	{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
	{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
	{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
	{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
};
int s7[4][16] = {
	{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
	{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
	{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
	{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
};
int s8[4][16] = {
	{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
	{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
	{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
	{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
};
string P(string strHEX) {
	string strBIN = hex_to_bin(strHEX);
	int p_table[32] = {
		16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10
		,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };
	string temp_str = "";
	for (int i = 0; i < 32; i++) {
		p_table[i] -= 1;
		temp_str += strBIN[p_table[i]];
	}
	return bin_to_hex(temp_str);
}
string int_to_bin(int num) {
	string f = "";
	while (num >= 1) {
		f += (num % 2) ? '1' : '0';
		num = num / 2;
	}
	string BIN = "";
	for (int i = 0; i < f.length(); i++) {
		BIN += f[f.length() - i - 1];
	}
	return BIN;
}
int bin_to_int(string BIN) {
	int NUM = 0; int f;
	for (int i = 0; i < BIN.length(); i++) {
		f = (BIN[i] == '1') ? 1 : 0;
		NUM += f*pow(2, BIN.length() - i - 1);
	}
	return NUM;
}
string S_BOX(string total_sub, int sub_table[4][16]) {
	//this is the only function to have a binary input/output
	string sub;
	sub = total_sub[0];
	sub += total_sub[5];
	string plainsub = total_sub.substr(1, 4);
	string ciphertext = int_to_bin(sub_table[bin_to_int(sub)][bin_to_int(plainsub)]);
	while (ciphertext.length() < 4) {
		ciphertext.insert(0, 1, '0');
	}
	return ciphertext;
}
string IP_inv(string strHEX) {
	string strBIN = hex_to_bin(strHEX);
	int arr[64] = {
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7 };
	string cipherBIN = "1111111111111111111111111111111111111111111111111111111111111111";
	for (int i = 0; i < strBIN.length(); i++) {
		arr[i] -= 1;
		cipherBIN[arr[i]] = strBIN[i];
	}
	return bin_to_hex(cipherBIN);
}
string DES_function(string inputHEXA32, string keyHEXA48) {
	string before_s_boxesHEXA = xor (E(inputHEXA32), keyHEXA48);
	string bsBIN = hex_to_bin(before_s_boxesHEXA);
	string after_s_boxes =
		S_BOX(bsBIN.substr(0, 6), s1) + S_BOX(bsBIN.substr(6, 6), s2) +
		S_BOX(bsBIN.substr(12, 6), s3) + S_BOX(bsBIN.substr(18, 6), s4) +
		S_BOX(bsBIN.substr(24, 6), s5) + S_BOX(bsBIN.substr(30, 6), s6) +
		S_BOX(bsBIN.substr(36, 6), s7) + S_BOX(bsBIN.substr(42, 6), s8);
	string afHEXA = bin_to_hex(after_s_boxes);
	string ROUND_end = P(afHEXA);
	return ROUND_end;
}
string DES_round(string inputHEXA, string keyHEXA) {
	string left = inputHEXA.substr(0, 8);
	string right = inputHEXA.substr(8, 8);
	string after_DES_function = DES_function(right, keyHEXA);
	string right_1 = xor (left, after_DES_function);
	string left_1 = right;
	return (left_1 + right_1);
}
struct keys {
	string now_subkey, next_subkey;
};
keys DES_subkey(string keyHEXA56) {
	string next_subkey = cir(keyHEXA56);
	string now_subkey = PC_2(next_subkey);
	return keys{ now_subkey,next_subkey };
}
string DES_rounds(string plainHEXA, string keyHEXA, int no_rounds = 1) {
	string key = PC_1(keyHEXA);
	string input = IP(plainHEXA);
	string key_next = key; string key_now;
	for (int i = 0; i < no_rounds; i++) {
		key_now = DES_subkey(key_next).now_subkey;
		key_next = DES_subkey(key_next).next_subkey;
		input = DES_round(input, key_now);
	}
	input = input.substr(8, 8) + input.substr(0, 8); //32bit swap
	return IP_inv(input);
}
string DES_enc(string plainHEXA, string keyHEXA, int no_itr = 1) {
	string NOW_plainHEXA = plainHEXA;
	for (int i = 0; i < no_itr; i++) {
		NOW_plainHEXA = DES_rounds(NOW_plainHEXA, keyHEXA, 16);
	}
	return NOW_plainHEXA;
}
int main() {
	string plain, key, cipher;
	while (1) {
		cout << "-Enter the plaintext(HEX): "; 
		cin >> plain; 
		cout << "-------Enter the key(HEX): "; 
		cin >> key; 
		cipher = DES_enc(plain, key, 1);
		cout <<endl <<"--Cipher text produced is: "<< cipher << endl <<endl;
	}
}