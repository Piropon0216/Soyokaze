# Rewrite Copilot Instructions Domain (Soyokaze Fork)
_Created: 2025-10-04T02:05:00Z_

## Context
- 既存 `copilot-instructions.md` が FinTech/AgenticRAG 前提だったため、Soyokaze ランチャー個人フォーク向けに CLEAR セクションを再定義。

## Change
- CLEAR OVERVIEW をランチャー操作/キーワード→コマンド解決ドメインへ書き換え
- E/A/R ルールを最小実装指向 (TDD / 小差分 / ハードコード開始) に更新

## Impact / Risk
- ドキュメントのみ。生成ポリシーの参照内容が適合化し誤誘導リスク低下。

## Test
- Markdown レンダリング確認
- 旧 FinTech 用語が該当セクションから除去されたことを確認

## Next
- StockResolver 機能追加 TDD 着手 (別 Changelog)
