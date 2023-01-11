#include "TextManager.h"
#include <map>

/// <summary>
/// 日本語のテキスト管理
/// </summary>
namespace TextManager
{
	//日本語表示するための連想配列
	std::map<wchar_t, int> text;

	//初期化
	void TextManager::Initialize()
	{
		text[L'あ'] = 0;  text[L'い'] = 1; text[L'う'] = 2; text[L'え'] = 3; text[L'お'] = 4;
		text[L'か'] = 5;  text[L'き'] = 6; text[L'く'] = 7; text[L'け'] = 8; text[L'こ'] = 9;
		text[L'さ'] = 10; text[L'し'] = 11;text[L'す'] = 12;text[L'せ'] = 13;text[L'そ'] = 14;
		text[L'た'] = 15; text[L'ち'] = 16;text[L'つ'] = 17;text[L'て'] = 18;text[L'と'] = 19;
		text[L'な'] = 20; text[L'に'] = 21;text[L'ぬ'] = 22;text[L'ね'] = 23;text[L'の'] = 24;
		text[L'は'] = 25; text[L'ひ'] = 26;text[L'ふ'] = 27;text[L'へ'] = 28;text[L'ほ'] = 29;
		text[L'ま'] = 30; text[L'み'] = 31;text[L'む'] = 32;text[L'め'] = 33;text[L'も'] = 34;
		text[L'や'] = 35; text[L'ゆ'] = 36;text[L'よ'] = 37;					   
		text[L'ら'] = 38; text[L'り'] = 39;text[L'る'] = 40;text[L'れ'] = 41;text[L'ろ'] = 42;
		text[L'わ'] = 43; text[L'を'] = 44;text[L'ん'] = 45;					   
		text[L'ゃ'] = 46; text[L'ゅ'] = 47;text[L'ょ'] = 48;					   
		text[L'ア'] = 49; text[L'イ'] = 50;text[L'ウ'] = 51;text[L'エ'] = 52;text[L'オ'] = 53;
		text[L'カ'] = 54; text[L'キ'] = 55;text[L'ク'] = 56;text[L'ケ'] = 57;text[L'コ'] = 58;
		text[L'サ'] = 59; text[L'シ'] = 60;text[L'ス'] = 61;text[L'セ'] = 62;text[L'ソ'] = 63;
		text[L'タ'] = 64; text[L'チ'] = 65;text[L'ツ'] = 66;text[L'テ'] = 67;text[L'ト'] = 68;
		text[L'ナ'] = 69; text[L'ニ'] = 70;text[L'ヌ'] = 71;text[L'ネ'] = 72;text[L'ノ'] = 73;
		text[L'ハ'] = 74; text[L'ヒ'] = 75;text[L'フ'] = 76;text[L'ヘ'] = 77;text[L'ホ'] = 78;
		text[L'マ'] = 79; text[L'ミ'] = 80;text[L'ム'] = 81;text[L'メ'] = 82;text[L'モ'] = 83;
		text[L'ヤ'] = 84; text[L'ユ'] = 85;text[L'ヨ'] = 86;					   
		text[L'ラ'] = 87; text[L'リ'] = 88;text[L'ル'] = 89;text[L'レ'] = 90;text[L'ロ'] = 91;
		text[L'ワ'] = 92; text[L'ヲ'] = 93;text[L'ン'] = 94;					   
		text[L'ャ'] = 95; text[L'ュ'] = 96;text[L'ョ'] = 97;					   
		text[L'a']  = 98; text[L'b']  = 99;text[L'c'] = 100;text[L'd'] = 101;text[L'e'] = 102;
		text[L'f'] = 103; text[L'g'] = 104;text[L'h'] = 105;text[L'i'] = 106;text[L'j'] = 107;
		text[L'k'] = 108; text[L'l'] = 109;text[L'm'] = 110;text[L'n'] = 111;text[L'o'] = 112;
		text[L'p'] = 113; text[L'q'] = 114;text[L'r'] = 115;text[L's'] = 116;text[L't'] = 117;
		text[L'u'] = 118; text[L'v'] = 119;text[L'w'] = 120;text[L'x'] = 121;text[L'y'] = 122;
		text[L'z'] = 123;													  
		text[L'A'] = 124; text[L'B'] = 125;text[L'C'] = 126;text[L'D'] = 127;text[L'E'] = 128;
		text[L'F'] = 129; text[L'G'] = 130;text[L'H'] = 131;text[L'I'] = 132;text[L'J'] = 133;
		text[L'K'] = 134; text[L'L'] = 135;text[L'M'] = 136;text[L'N'] = 137;text[L'O'] = 138;
		text[L'P'] = 139; text[L'Q'] = 140;text[L'R'] = 141;text[L'S'] = 142;text[L'T'] = 143;
		text[L'U'] = 144; text[L'V'] = 145;text[L'W'] = 146;text[L'X'] = 147;text[L'Y'] = 148;
		text[L'Z'] = 149;													  
		text[L'!'] = 150; text[L'%'] = 151;text[L'('] = 152;text[L')'] = 153;text[L'*'] = 154;
		text[L'+'] = 155; text[L','] = 156;text[L'-'] = 157;text[L'.'] = 158;text[L'/'] = 159;
		text[L':'] = 160; text[L';'] = 161;text[L'<'] = 162;text[L'>'] = 163;text[L'?'] = 164;
		text[L'@'] = 165; text[L'['] = 166;text[L']'] = 167;text[L'_'] = 168;text[L'{'] = 169;
		text[L'}'] = 170;													  
		text[L'0'] = 171; text[L'1'] = 172;text[L'2'] = 173;text[L'3'] = 174;text[L'4'] = 175;
		text[L'5'] = 176; text[L'6'] = 177;text[L'7'] = 178;text[L'8'] = 179;text[L'9'] = 180;
		text[L'が'] = 192;text[L'ぎ'] = 193;text[L'ぐ'] = 194;text[L'げ'] = 195;text[L'ご'] = 196;
		text[L'ざ'] = 197;text[L'じ'] = 198;text[L'ず'] = 199;text[L'ぜ'] = 200;text[L'ぞ'] = 201;
		text[L'だ'] = 202;text[L'づ'] = 203;text[L'で'] = 204;text[L'ど'] = 205;
		text[L'ば'] = 206;text[L'び'] = 207;text[L'ぶ'] = 208;text[L'べ'] = 209;text[L'ぼ'] = 210;
		text[L'ガ'] = 211;text[L'ギ'] = 212;text[L'グ'] = 213;text[L'ゲ'] = 214;text[L'ゴ'] = 215;
		text[L'ザ'] = 216;text[L'ジ'] = 217;text[L'ズ'] = 218;text[L'ゼ'] = 219;text[L'ゾ'] = 220;
		text[L'ダ'] = 221;text[L'ヅ'] = 222;text[L'デ'] = 223;text[L'ド'] = 224;
		text[L'バ'] = 225;text[L'ビ'] = 226;text[L'ブ'] = 227;text[L'べ'] = 228;text[L'ボ'] = 229;
		text[L'ぱ'] = 230;text[L'ぴ'] = 231;text[L'ぷ'] = 232;text[L'ぺ'] = 233;text[L'ぽ'] = 234;
		text[L'パ'] = 235;text[L'ピ'] = 236;text[L'プ'] = 237;text[L'ペ'] = 238;text[L'ポ'] = 239;
	}

	//文字の対応する番号を取得
	int TextManager::GetNumber(wchar_t t) { return text[t];}
}