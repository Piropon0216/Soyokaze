# Gitignore: ignore local/workspace and temp files
_Created: 2025-10-04T01:50:00Z_

## Context
- リポジトリに追加されたテンプレート群やローカルワークスペースファイルを追跡対象から外し、リポジトリをクリーンに保つための更新。

## Change
- `.gitignore` に以下を追加: `.vscode/`, `.idea/`, `.github/chatmodes/`, `AGENTS/`, `dist/`, `bin/`。

## Impact / Risk
- 追跡対象から外れるだけで、既存のソースやドキュメントには影響なし。もし意図的に `AGENTS/` をコミットしたい場合は `.gitignore` を修正してください。

## Test
- git status で不要ファイルが未追跡として表示されないことを確認

## Next
- 必要に応じて `.gitattributes` を追加して改行コードポリシーを統一する。
