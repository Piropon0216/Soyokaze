# Soyokaze 用: Shared Instructions Template - 適用ガイド (プロジェクトカスタム版)

目的: `APPLY_TEMPLATE_GUIDE.md` の短縮版を Soyokaze プロジェクト向けに調整した最短適用手順を記載します。
想定環境: Windows + PowerShell。Node.js は不要（このプロジェクトは C++/MFC であり、テンプレート適用はドキュメント運用に限定）。

## 早見手順（最小・Soyokaze 向け）
1. ブランチ作成（安全）
   - git checkout -b chore/apply-instructions-soyokaze
2. 既存 `doc` と `.github/instructions` の差分を確認
   - PowerShell:
     ```powershell
     git status --porcelain
     git diff -- doc\APPLY_TEMPLATE_GUIDE.md .github\instructions\apply_template_soyokaze.md
     ```
3. Dry-run の代替: 手動レビュー
   - このリポジトリはネイティブアプリのドキュメント中心のため、自動化スクリプトは不要。まずは `doc` 内のファイルを目視で確認してください。
4. 実適用
   - 変更を `instructions/` に追加し、`doc` に影響があれば逐次編集。
5. チェック
   - Markdown のリンクが切れていないか確認（`npm` がない場合は目視での確認でOK）

## 主要プレースホルダ（本プロジェクトでは該当箇所が少ない）
- __TEMPLATE_PROJECT_NAME__ → Soyokaze
- __TEMPLATE_ORG__ → Piropon0216（fork 所有者）

## チェックリスト（適用後）
- [ ] `doc/changelogs/YYYY-MM-DD-*.md` を追加（CHANGELOG FIRST）
- [ ] `.github/copilot-instructions.md` のプロジェクト特記事項を追加
- [ ] `instructions/` 内のファイルが .github 配下にあることを確認

## 安全運用の注意点（Soyokaze 向け）
- このプロジェクトはフォーク元に PR を出さない方針のため、`.github/workflows` の自動化を上書きする場合は慎重に（プライベート運用のみ）。
- 重要ファイル（LICENSE, src, doc）は自動置換しないこと。

## 次の推奨アクション
1. `instructions/` に `usage.instructions.md`（ユーザ向けの簡易手順）を追加
2. `doc/RUNBOOK.md` を見直し、必要に応じて画像リンクを修正
3. `doc/changelogs/` にこの変更の Changelog を追加

---
このファイルは Soyokaze のローカルカスタム指示として保持してください。フォーク元へ PR は行わない方針です。
