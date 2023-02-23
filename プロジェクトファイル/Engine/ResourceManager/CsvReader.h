#pragma once
#include <string>
#include <vector>

/// <summary>
/// 外部から情報を持ってくるクラス
/// </summary>
class CsvReader {

	//構造体(一行)
	struct LINEREC {
		std::vector<std::string> record;
	};

	//全ての文字格納用
	std::vector<LINEREC> all;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="filename">ファイルの名前</param>
	CsvReader(std::string filename);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CsvReader();

	/// <summary>
	/// 読み込んだファイルが何行あるか
	/// </summary>
	/// <returns>総行数</returns>
	int GetLines();

	/// <summary>
	/// 指定行数の中の総行数を返す
	/// </summary>
	/// <param name="line">行数</param>
	/// <returns>指定行数の中の総行数</returns>
	int GetColumns(int line);

	/// <summary>
	/// 指定した(行数,->の中の行数)の文字列を返す
	/// </summary>
	/// <param name="line">行数</param>
	/// <param name="column">行数,->の中の行数</param>
	/// <returns>行数,->の中の行数の文字列</returns>
	std::string GetString(int line, int column);

	/// <summary>
	/// 指定した(行数,->の中の行数)のワイド文字列を返す
	/// </summary>
	/// <param name="line">行数</param>
	/// <param name="column">行数,->の中の行数</param>
	/// <returns>行数,->の中の行数の文字列</returns>
	const wchar_t* GetWchar(int line, int column);

	/// <summary>
	/// 指定した(行数,->の中の行数)の整数を返す
	/// </summary>
	/// <param name="line">行数</param>
	/// <param name="column">行数,->の中の行数</param>
	/// <returns>行数,->の中の行数の整数</returns>
	int GetInt(int line, int column);

	/// <summary>
	/// 指定した(行数,->の中の行数)の浮動小数点を返す
	/// </summary>
	/// <param name="line">行数</param>
	/// <param name="column">行数,->の中の行数</param>
	/// <returns>行数,->の中の行数の浮動小数点</returns>
	float GetFloat(int line, int column);

};
