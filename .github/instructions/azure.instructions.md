# Azure Instructions

## Scope
Azure リソース設計・デプロイ・運用に関する統一ガイド。FinTech(マーケットデータ/NL 分析) 特性を踏まえた最小コスト & セキュア構成。

## Core Principles
- Least Privilege + Managed Identity (すべての Functions / 将来の Container)
- IaC First: 変更は Bicep -> PR -> Validate -> Deploy
- Observability by Default: App Insights + (将来) Log Analytics クエリテンプレ
- Cost Guardrails: Free/Tier1 を起点, 拡張時は事前コスト試算 (docs/poc_cost_estimate_2025-09-13.md)

## Resource Baseline (MVP)
| Layer | Service | Purpose | Notes |
|-------|---------|---------|-------|
| Compute | Azure Functions (Python) | Orchestration / Agents | v4, isolated dependencies minimal |
| Data | Storage Account (Blob) | 原データ + 生成特徴量 parquet | container per domain |
| Data | (Local DuckDB + Blob sync) | クエリ実行/一時集計 | バッチで差分アップロード |
| Monitoring | Application Insights | 分散トレース/メトリクス | sampling 5%→調整可能 |
| Identity | User Assigned Managed Identity | Secrets-less auth | Key Vault 追加予定 |

## Deployment Flow (CLEAR)
### 要求の核心
"安全で再現可能な段階的デプロイ" を最小構成で確立する。

### 実装手順
1. Bicep Lint & What-If (dry-run)
2. functions build (テスト完了後)
3. azd deploy (ステージング) → Smoke Test
4. Promote to prod slot (将来)

### 技術仕様
- Bicep version: latest stable (az cli pinned)
- Extension Bundles: [4.*, 5.0.0)
- Python Runtime: 3.11
- Logging: Structured JSON (timestamp, level, correlationId)
- 制約: 起動遅延許容 Cold Start < 3s (目安)

### 期待する成果物
- [ ] what-if 成功ログ (CI アーティファクト)
- [ ] deploy run log + endpoint health OK

### セキュリティ / ガードレール
- すべての外部API鍵 → (将来) Key Vault 参照 placeholder
- RBAC: Reader / Contributor 分離 (自動化 ID には最小権限)
- 通信: HTTPS enforce, public network 最小化 (将来 VNet)

## Operational Checklists
- 毎日: Application Insights 失敗率 < 2%
- 週次: コスト差分 / 前週 ±15% 超過で調査

## Failure Handling
| Event | Action |
|-------|--------|
| Function timeout | retry (指数 backoff 3) + degraded flag | 
| Blob write 409 | 冪等: 再計算スキップ / メタ更新 | 
| what-if 差分過多 | レビューブロック / 要 Changelog | 

## References
- .github/copilot-instructions.md (メイン統合)
- docs/infra_modular_design_2025-09-14.md
- docs/functions_deploy_run_from_package.md
