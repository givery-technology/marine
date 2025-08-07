#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

/**
 * ディレクトリを再帰的に走査してtrack.ymlまたはbook.ymlファイルを検索
 * @param {string} dirPath - 検索するディレクトリパス(contentsディレクトリからの相対パス)
 * @param {string} basePath - 基準となるディレクトリパス（相対パス計算用）
 * @param {string[]} results - 見つかったファイルパスを格納する配列
 */
function findYamlFiles(dirPath, basePath, results = []) {
  try {
    const entries = fs.readdirSync(dirPath, { withFileTypes: true });

    for (const entry of entries) {
      const fullPath = path.join(dirPath, entry.name);

      if (entry.isDirectory()) {
        // サブディレクトリを再帰的に検索
        findYamlFiles(fullPath, basePath, results);
      } else if (entry.isFile()) {
        // track.yml または book.yml をチェック
        if (entry.name === 'track.yml' || entry.name === 'book.yml') {
          const relativePath = path.relative(basePath, fullPath);
          results.push(relativePath);
        }
      }
    }
  } catch (error) {
    console.error(`エラー: ディレクトリ "${dirPath}" を読み込めません: ${error.message}`);
  }

  return results;
}

/**
 * メイン関数
 */
function main() {
  // コマンドライン引数を取得
  const args = process.argv.slice(2);

  if (args.length !== 1) {
    console.error('使用方法: node script.js <ディレクトリパス>');
    process.exit(1);
  }

  const targetDir = "contents/" + args[0];

  // ディレクトリの存在確認
  if (!fs.existsSync(targetDir)) {
    console.error(`エラー: ディレクトリ "${targetDir}" が存在しません`);
    process.exit(1);
  }

  // ディレクトリかどうか確認
  if (!fs.statSync(targetDir).isDirectory()) {
    console.error(`エラー: "${targetDir}" はディレクトリではありません`);
    process.exit(1);
  }

  // YAML ファイルを検索
  const foundFiles = findYamlFiles(targetDir, "contents");

  // 結果を出力
  if (foundFiles.length === 0) {
    console.log('track.yml または book.yml ファイルが見つかりませんでした');
  } else {
    foundFiles.forEach(filePath => {
      console.log(filePath);
    });
  }
}

// スクリプトが直接実行された場合のみメイン関数を実行
if (require.main === module) {
  main();
}