# GitHub Copilot Custom Instructions (Main)
## PURPOSE
FinTech 向け AgenticRAG / NL→分析 プラットフォームでの一貫した自動生成品質を最大化するための中枢インストラクション。詳細は専門ファイル (`.github/instructions/*.md`) へ委譲。

## INDEX (Specialized Instructions)
| Area | File | Summary |
|------|------|---------|
| Azure | `instructions/azure.instructions.md` | IaC / デプロイ / セキュリティ / ガードレール |
| Backend | `instructions/backend.instructions.md` | Functions + 分析ロジック CLEAR 実行指針 |
| Frontend | `instructions/frontend.instructions.md` | React + TS UI / チャート / 体験最適化 |
| Testing | `instructions/testing.instructions.md` | テストピラミッド / カバレッジ戦略 |
| Coding Policy | `instructions/backend-coding-policy.instructions.md` | スタイル / 依存 / 例外規約 |
| Naming | `instructions/backend-naming-convention.instructions.md` | 指標/DSL/ファイル命名規約 |
| Agents Context | `../AGENTS/AGENTS.md` | エージェント一覧 / 協調ルール |

## CLEAR OVERVIEW
### C (Concise) 要求の核心
金融ドメインの自然言語要求を セキュア / 冪等 / 追跡可能 な分析結果 (指標+特徴量+可視化) へ高速変換する統合ルールを提供する。

### L (Logical) ロジック構造
1. 入力検証 (NL 正規化, ドメイン語彙マッピング)
2. プラン生成 (DSL) → バリデーション (命名/期間/メトリク衝突)
3. エージェント並列実行 (マーケットデータ, 特徴量, スコアリング)
4. 結果統合 (型安全 + degraded 記録) → 可視化モデル変換
5. 監視 (ログ/メトリク/トレース) & コスト/品質フィードバック

### E (Explicit) 明示的ルール TOP 10
1. CHANGELOG FIRST (全機能/仕様変更) 事前ドラフト必須
2. TDD / Coverage Gate: 重要モジュール 100%, 全体 >=85%
3. 破壊的変更は `Impact` 明記 + metrics alias migration 方針
4. Azure 資源変更: Bicep what-if 差分レビュー通過なしでデプロイ禁止
5. Secrets/Keys をコード/設定直書き禁止 (Managed Identity 前提, 将来 Key Vault)
6. エージェント間の直接依存禁止 (オーケストレーター経由)
7. ログは構造化 JSON + correlationId 必須
8. 関数 or pure transformation 優先 (Class 多用禁止)
9. 生成物(コード/DSL)は命名規約ファイル準拠 (衝突時 alias)
10. 30分超のデバッグ / 設計判断は lessons へ 3行以上追記

### A (Actionable) 実行指針 (日常フロー)
1. 要求受領: CLEAR テンプレで Issue 下書き (核心/手順/仕様/成果物/関連)
2. Red: 期待テスト追加 → Green 実装 → Refactor (重複/副作用除去)
3. Coverage 計測 & 欠落テスト追加
4. Changelog 作成 (Context/Change/Impact/Test/Next)
5. Bicep what-if / Lint / Unit / Integration → すべて green
6. 単一コミット (ISO8601 prefix + conventional commit) → PR
7. PR で schema diff / coverage delta チェック

### R (Relevant) プロジェクト文脈
既存ドキュメントでの設計背景・ルール補強:
- `docs/PROJECT_OVERVIEW.md` 全体像
- `docs/agent_handoff_lessons.md` 問題解決知見
- `docs/plan_nl_stock_query_poc_2025-09-14.md` NL→株式クエリPoc
- `docs/plan_per_metric_change_pipeline_2025-09-16.md` 特徴量変化率
- `docs/nl_sql_value_change_semantics.md` change/diff セマンティクス
- `docs/nl_sql_diff_multi_sort_plan.md` 複合ソート/差分列

---
## CONSOLIDATED KEY RULES (詳細は各専門ファイルへ移管)

### 1. CHANGELOG & COMMIT DISCIPLINE
省略禁止: 目的/差分/リスク/テスト/次の一歩。Trial & Error 条件発生時は必ず記録。

### 2. テスト & カバレッジ
`npm run test:coverage` / Python 部分は将来統合。新規機能は baseline 100% で開始し許容低下なし。

### 3. Azure デプロイ
`what-if` 差分 > 10 リソース または 破壊的 (delete/replace) → 追加レビュータグ `infra-review` 必須。

### 4. エージェント連携
計画 (planId) -> fan-out -> gather -> aggregate の4段階ログを correlationId で連結。

### 5. ドメイン命名
metrics / features は naming instructions に従い DSL 生成前にバリデーション。

### 6. セキュリティ最小要件
PII なし想定だが、ログ中 symbol はハッシュ (将来オプション) 設定可能に設計。

---
## QUALITY CHECKLIST (PR Template Short)
- [ ] Changelog 添付
- [ ] テスト (正常/異常/境界)
- [ ] Coverage 目標達成
- [ ] Bicep what-if 差分貼付
- [ ] 命名規約違反なし
- [ ] ログフィールド (correlationId, planId) 追加
- [ ] Markdown リンクチェック (`npm run check:links`) パス
- [ ] トレーサビリティマトリクス生成 (`npm run trace:matrix -- --fail-on-gaps`) ギャップなし
- [ ] ブランチ命名規約順守 (below Branch Strategy)

### Branch Strategy
| Branch | 用途 | 保護設定(推奨) |
|--------|------|----------------|
| `main` | 常に deploy 可能 / リリースタグ起点 | 必須レビュー / CI 成功 / squash | 
| `develop` (任意) | 機能集約 (必要時) | 同上 (緩め可) |
| `feat/*` | 機能追加 (`feat/metric-registry`) | PR → main/develop |
| `fix/*` | バグ修正 | PR → main/develop |
| `chore/*` | 雑務/依存更新 | PR |
| `exp/*` | 実験 (破棄前提) | 原則 1 人 / 期限短 |

Branch 命名: `<type>/<kebab-case-topic>` / 1 Issue = 1 Branch 原則。
リベース方針: 長期ブランチ化回避のため 1 日超える作業は最小差分で早期統合。
コンフリクト発生時: `git rerere` 利用推奨 / 解決後再テスト必須。

---
## FUTURE TRACK (Roadmap Snapshot)
- ベクトル検索導入 & news-signal embedding
- 特徴量カタログ self-describing JSON registry
- Mutation Testing 導入
- Azure Cost Anomaly Alert

---
## APPENDIX: CHANGELOG WORKFLOW (保持)
1. Issue/要求/アイデア簡潔整理
2. Red テスト or 期待仕様テスト化
3. 実装 + リファクタ
4. Changelog Draft
5. 全テスト/リンタ/型/coverage gate
6. 単一コミット + PR (リンク)
7. lessons 更新 (必要時)

タイムスタンプ: `_Created:` は UTC 実時刻固定 / コミットメッセージ同一。

---
## REFERENCES QUICK MAP
| Category | Doc |
|----------|-----|
| Overview | PROJECT_OVERVIEW.md |
| Lessons | agent_handoff_lessons.md |
| NL Plans | plan_nl_stock_query_poc_2025-09-14.md |
| Features | plan_per_metric_change_pipeline_2025-09-16.md |
| Semantics | nl_sql_value_change_semantics.md |
| Diff/Multi-sort | nl_sql_diff_multi_sort_plan.md |

---
このメインファイルはハイレベル集約のみを提供し、詳細更新は専門ファイル追加で行い過剰肥大化を防ぐ。

### 1. 🚀 **段階的・検証型作業/TDD（テスト駆動開発）+ CHANGELOG駆動コミット 原則の適用**
- **MUST**: Azure Functions開発時は分割実行（段階的デプロイ）
- **MUST**: Bicep IaCテンプレートのDry Run での事前確認
- **MUST**: エラーチェック後のGitコミット
- **WHY**: 安全性・品質確保、Azure課金制御
- **MUST**: TDDを実施する。コード生成するときは、それに対応するユニットテストを常に生成する。
            TypeScriptコードを追加で修正したとき、'npm test'がパスすることを常に確認する。
- **MUST**: すべての意味あるコミット(機能追加/仕様変更/リファクタ/バグ修正/テスト追加)の直前に、`docs/changelogs/` 配下へ日付(YYYY-MM-DD) + スラッグ 形式のMarkdownを追加/更新し、目的・変更点・影響範囲・テスト観点を記述する ("CHANGELOG FIRST").
- **MUST**: すべてのコミットメッセージは UTC ISO8601日時プレフィックスで開始すること (例: `2025-09-12T06:41:23Z feat: add X`). フォーマット: `YYYY-MM-DDTHH:MM:SSZ <Conventional Commit 本体>`。これにより後続の時系列分析と設計判断の追跡を容易化する。
- **MUST**: コミット順序は (1) 変更コード & テスト追加 → (2) 新規/更新Changelog追加 → (3) まとめて単一コミット。Changelogを含まない機能系コミットは禁止。
- **MUST**: Changelogファイル命名規則: `YYYY-MM-DD-<slug>.md`。同日に複数あれば差分内容が判別できる短いケバブケースslugを利用。
- **MUST**: Changelog最小テンプレート:
  ```md
  # タイトル (短く)
  _Created: YYYY-MM-DDTHH:MM:SSZ_
  ## Context
  - 背景/目的
  ## Change
  - 主要変更点 箇条書き
  ## Impact / Risk
  - 影響範囲 / マイグレーション / 破壊的変更有無
  ## Trial & Error
  - 試行錯誤・失敗→修正の主要ステップを番号付きで簡潔に (閾値調整/テスト不整合/設計判断/失敗理由)
  ## Test
  - 追加/更新されたテスト一覧 or 観点
  ## Next
  - 後続タスク (任意)
  ```
  - **NEW MUST**: 機能追加/仕様変更で一度でもテスト失敗や閾値調整・アルゴリズム差し替えが発生した場合、`## Trial & Error` セクションを必ず記述すること。含める内容:
    1. 問題発生時の症状 (テスト名/エラーメッセージ要約)
    2. 原因仮説 → 検証手段 (再現条件, データ特性など)
    3. 適用した修正 (閾値変更/ロジック変更/列除外など)
    4. 結果 (テストパス/副作用/残リスク)
    5. 学習ポイント (再発防止 or 次回最適化指針)
  - **WHY**: 将来の閾値再調整やヒューリスティック拡張時に履歴を参照し、同じ判断コストを繰り返さないため。
- **RECOMMENDED**: 大きな変更を分割する場合は段階ごとにミニマムなChangelogを積み上げ、最後に統合サマリを書く。
- **NEVER**: 後追いでまとめて複数日の変更を1つのChangelogに集約しない。
- **WHY**: 教育的トレーサビリティ・設計意図の永続化・レビュアビリティ向上。

---
Note for this fork: This fork is used for personal/custom development only. Do not create pull requests to the original upstream repository. Project-specific instructions live under `.github/instructions/` and `doc/APPLY_TEMPLATE_GUIDE.md`.
```ts
// 例: エージェント関数のテスト
function processWeatherData(temp: number, humidity: number): WeatherResult {
  return { maxTemp: temp, conditions: humidity > 80 ? 'humid' : 'dry' };
}

test("気温34度、湿度85%で正しく処理される", () => {
  expect(processWeatherData(34, 85)).toEqual({ maxTemp: 34, conditions: 'humid' });
});
```
- **MUST**: 各ファイルの冒頭にはコメントで仕様を記述すること。
```ts
/**
 * 気象データを取得し、電力需要予測に必要な形式に変換する
 * @param date 対象日付 (YYYY-MM-DD)
 * @returns 気象データオブジェクト
 **/
export async function fetchWeatherData(date: string): Promise<WeatherData> {
  // 実装
}
```
- **MUST**: TypeScriptで関数型ドメインモデリングを行う。Classを出来るだけ使わず、関数による実装を優先。代数的データでドメインをモデリングする。
```ts
// AgenticRAG用の型定義例
type AgentResult<T, E> = {
    success: true;
    data: T;
    agentId: string;
    timestamp: Date;
} | {
    success: false;
    error: E;
    agentId: string;
    timestamp: Date;
}

type PowerDemandForecast = {
  predictedPeak: number;  // kW
  confidence: number;     // 0-1
  factors: WeatherFactor[];
}
```
- **MUST**: カバレッジに基づくテストの自動生成。テストカバレッジ100%を目指す。'*.ts'に対して, '*.test.ts'でユニットテストをかく。
1. 'npm run test:coverage'を実行し、現在のカバレッジ取得
2. 今の状態から最もカバレッジが上がるテストコードを考察してから追加
3. 再度カバレッジ計測し、数値が向上していることを確認
- **MUST**: 以下のモノレポの配置規則に従う。
```
frontend/              # TypeScriptフロントエンド
  src/
    components/        # React/Vue コンポーネント
    services/          # API呼び出しサービス
    types/            # 型定義
    utils/            # ユーティリティ関数
    __tests__/        # テストファイル
infra/                # Bicep IaCテンプレート
  main.bicep
  main.parameters.json
src/agenticrag-functions/ # Python Azure Functions
  *.py              # 各エージェント実装
  host.json         # Functions設定
  requirements.txt  # 依存関係
docs/                 # ドキュメント
```

### 2. 📁 **プロジェクト構造原則**
- **MUST**: `infra/`配下のBicepファイルが単一の信頼できる情報源
- **MUST**: `src/agenticrag-functions/`配下でPython Azure Functions実装
- **MUST**: `frontend/`配下でTypeScript/React実装
- **NEVER**: 重複ファイルの作成・編集禁止
- **WHY**: マルチサービス構成での一貫性維持

### 3. 🔧 **Azure開発・デプロイ最適化**
- **MUST**: Azure Developer CLI (azd) でのデプロイ管理
- **MUST**: ユーザー割り当て管理IDによる安全な認証
- **MUST**: Application Insightsでの詳細監視設定
- **CONFIG**: Durable Functions最適化設定適用済み
- **WHY**: 本番レベルのAzure環境構築

### 4. 📝 **AgenticRAGアーキテクチャ遵守**
- **MUST**: ファンアウト・ファンインパターンの実装
- **REQUIRED**: オーケストレーター、各エージェント、統合レスポンス
- **STANDARD**: 電力業界シナリオに基づく実装
- **WHY**: リアルな業務要件への対応

### 5. 🔄 **マルチエージェント連携管理**
- **COMPLETE**: 気象、過去データ、需要予測、災害対応エージェント
- **RULE**: 各エージェントの独立性と相互連携
- **NEVER**: エージェント間の密結合禁止
- **WHY**: スケーラブルなエージェント追加・変更

---

## 📋 開発時の具体的ガイドライン

### TypeScriptフロントエンド開発時

#### 必須ファイル構造
```typescript
// types/agentic-rag.ts - 型定義
export interface QueryRequest {
  query: string;
  context?: {
    industry: 'power' | 'manufacturing' | 'finance';
    urgency: 'low' | 'medium' | 'high';
  };
}

export interface AgentResponse {
  agentId: string;
  result: any;
  timestamp: Date;
  processingTime: number;
}

export interface OrchestrationResult {
  requestId: string;
  query: QueryRequest;
  agentResults: AgentResponse[];
  finalAnswer: string;
  confidence: number;
}
```

#### React コンポーネント実装原則
- **MUST**: 関数コンポーネント + TypeScript
- **MUST**: カスタムフックでロジック分離
- **MUST**: エラーハンドリング組み込み

```typescript
// hooks/useAgenticRAG.ts
export const useAgenticRAG = () => {
  const [loading, setLoading] = useState(false);
  const [result, setResult] = useState<OrchestrationResult | null>(null);
  const [error, setError] = useState<string | null>(null);

  const executeQuery = async (query: QueryRequest): Promise<void> => {
    // 実装
  };

  return { loading, result, error, executeQuery };
};
```

### Python Azure Functions開発時

#### エージェント実装パターン
```python
# 各エージェント共通のベース実装
from typing import Dict, Any, Union
import logging

class AgentResponse:
    def __init__(self, agent_id: str, data: Any, error: str = None):
        self.agent_id = agent_id
        self.data = data
        self.error = error
        self.timestamp = datetime.utcnow()

def weather_agent(input_data: Dict[str, Any]) -> AgentResponse:
    """気象データ取得エージェント"""
    try:
        # 実装
        return AgentResponse("weather", weather_data)
    except Exception as e:
        logging.error(f"Weather agent error: {e}")
        return AgentResponse("weather", None, str(e))
```

#### Bicep IaC開発時
- **MUST**: リソース名にresourceTokenを使用
- **MUST**: ユーザー割り当て管理IDでRBAC設定
- **MUST**: Application Insights統合
- **RECOMMENDED**: Free tierリソースでコスト最適化

### Git操作・デプロイ時
- **MUST**: 段階的add・commit（Azure Functions単位）
- **MUST**: `azd up`前にBicepエラーチェック
- **MUST**: Application Insightsでデプロイ後動作確認

---

## 🛠️ 推奨開発パターン

### フロントエンド開発時
1. **型定義**: `types/`で共通型定義
2. **API層**: `services/`でAzure Functions呼び出し
3. **コンポーネント**: `components/`で再利用可能なUI
4. **テスト**: `__tests__/`でユニット・統合テスト

### バックエンド開発時
1. **エージェント追加**: 新しい業務ドメインに対応
2. **オーケストレーター更新**: ファンアウト・ファンインロジック
3. **データソース連携**: Azure AI Search、外部API統合
4. **監視強化**: Application Insights カスタムメトリクス

### Azure環境構築時
1. **IaC優先**: 手動設定禁止、Bicepテンプレート使用
2. **段階デプロイ**: `azd up`での一括デプロイ
3. **セキュリティ**: 管理ID、Key Vault、最小権限
4. **監視**: 詳細ログ、メトリクス、アラート設定

---

## 🚫 禁止事項・注意点

### 絶対禁止
- ❌ Azure Function内でのハードコーディング（APIキー等）
- ❌ エージェント間の直接通信（オーケストレーター経由必須）
- ❌ フロントエンドでのAzure直接呼び出し（Functions経由必須）
- ❌ Bicepテンプレート外でのAzureリソース手動作成

### 注意事項
- ⚠️ Azure AI Search Free tierの制限（50MB、10,000ドキュメント）
- ⚠️ OpenAI APIの利用料金監視
- ⚠️ Durable Functions実行時間制限（5分）

---
## 🧭 ハンドオフ & 現行スプリント参照 (2025-09-15)
最新の優先タスクと Exit Criteria 一覧は `docs/HANDOFF_STATUS_2025-09-15.md` を参照。

P0 Exit Criteria (A-D):
- (A) Azure PoC: NL→HTTP Function→DuckDB 一回成功
- (B) Suggestions Scoring: 既存+新規7 heuristics 正規化上位K
- (C) feature_count_hist: 週次分布生成 & ドキュメント
- (D) plan_ineligible: 3分類 (user_error/transient/capacity) + メトリクス

Wave1 着手順序 (概要): Storage Adapter → Azure Function NL Query → HTTP Metrics → Nightly Changelog Audit CI → plan_ineligible 精緻化。

詳細: `docs/HANDOFF_STATUS_2025-09-15.md` / 過去知見: `docs/agent_handoff_lessons.md`。

---

## 📊 品質チェックポイント

### フロントエンド品質
- [ ] TypeScript型安全性
- [ ] React/Vue コンポーネント再利用性
- [ ] エラーハンドリング網羅性
- [ ] テストカバレッジ80%以上

### バックエンド品質
- [ ] Python Functions型ヒント適用
- [ ] エージェント独立性確保
- [ ] オーケストレーター堅牢性
- [ ] Application Insights統合

### インフラ品質
- [ ] Bicep Best Practices準拠
- [ ] RBAC最小権限適用
- [ ] コスト最適化設定
- [ ] 監視・アラート設定

---

## 🎯 AgenticRAG特有のベストプラクティス

### エージェント設計原則
1. **単一責任**: 各エージェントは一つの専門分野に特化
2. **ステートレス**: エージェント間で状態を共有しない
3. **冪等性**: 同じ入力に対して同じ出力を保証
4. **エラー許容**: 一部エージェントの失敗でも全体は継続

### データフロー管理
1. **入力検証**: オーケストレーターでの厳密な入力チェック
2. **並列処理**: 独立したエージェントは並列実行
3. **結果集約**: 型安全な結果マージング
4. **レスポンス最適化**: 不要なデータの除外

### 監視・運用
1. **分散トレーシング**: エージェント間の実行フロー追跡
2. **パフォーマンス監視**: 各エージェントの実行時間測定
3. **エラー分析**: エージェント別エラー率・パターン分析
4. **コスト監視**: Azure OpenAI使用量の継続監視

---

## 📚 ナレッジ / ハンドオフ参照集
以下のドキュメントは日々更新される運用・設計知見の集約ポイント。新しいエージェント実装やNL→SQL拡張、可視化機能追加前に必ず確認すること。

### コア知見ドキュメント
- `docs/agent_handoff_lessons.md`
  - テスト戦略・失敗しやすい落とし穴・NL→SQL設計原則・命名/列追加ポリシーまとめ
- `docs/backlog_current_status_2025-09-13.md`
  - 直近完了タスクと残タスクの体系。優先度P0/P1判断の前提になる。
- `docs/nl_sql_value_change_semantics.md`
  - value / change(比率) / diff(絶対値) 列の定義とNULL化(閾値ABS(prev)<1e-9)ルール
- `docs/nl_sql_diff_multi_sort_plan.md`
  - マルチメトリック ORDER チェーンと diff 列導入の設計背景

### 活用ガイド
1. NL→SQL機能追加時: semantics → diff/multi-sort plan → lessons の順で整合性確認
2. 新規列導入時: 既存の change/diff 命名規則( `<metric>_change`, `<metric>_diff`) との衝突回避
3. 複雑な期間比較追加時: lessons 内の "比較ウィンドウ非重複" セクションを遵守
4. Backlog着手前: backlog_current_status を更新 (完了/新規/降格 理由を短文化)

### 更新ポリシー
- 新しい分析列 or 重要パーサ拡張 → 先に plan ドキュメント化 → 実装 + テスト → lessons へ要約反映 → Changelog
- 既存ポリシー変更(破壊的可能性) → backlog に "migration note" 追記 → 関連テスト調整 → lessons 強調更新

### 最低限セルフチェック (抜粋)
- 新規列に semantic 重複はないか
- 比較ウィンドウが現行ロジックと重複していないか
- 変更メトリクスがユーザ指定メトリクス集合に属するか (UNKNOWN_CHANGE_METRIC 不発)
- 非数値分母 prev の閾値NULL化を損なっていないか

### 知見追加トリガー (問題解決学習)
- デバッグ/仕様検討に30分以上要したケース
- テストフレーク (再現条件と恒久対策)
- 突発的 schema 変更や命名衝突回避の判断根拠
- パフォーマンス劣化を招いた一時的ワークアラウンド (後で除去予定の TODO 併記)
> 上記が発生した場合は最小 3 行 (背景/原因/恒久策) を `agent_handoff_lessons.md` に追記し、対応Changelogを作成すること。

> このセクションを更新した場合は、必ず対応する Changelog を `docs/changelogs/` に追加し ISO8601 タイムスタンプ付きコミットで履歴化すること。

---

**重要**: このプロジェクトは本格的なAzure PaaSサービスを活用したAgenticRAGシステムです。上記ルールを遵守することで、実用レベルのマルチエージェント AI システムを構築できます。

---
## 📘 CHANGELOG 運用ワークフロー (詳細)
1. Issue/要求/アイデアを簡潔に整理 (ローカルメモ可)
2. 先にテスト (Red) を追加 or 期待仕様をテストに明文化
3. 実装 (Green) & リファクタ (Refactor)
4. Changelogドラフト作成 (Context/Change/Impact/Test/Next)
5. 全テスト/リンタ/型チェック実行 & カバレッジ確認
6. 変更差分 + Changelog を単一コミット (feat/fix/chore/docs など Conventional Commits 推奨)
7. PR作成時は該当Changelogを概要にリンク

チェックリスト (コミット前セルフレビュー):
- [ ] 新規/更新Changelogがある
- [ ] タイトル・日付命名規則に準拠
- [ ] 破壊的変更有無をImpactに明記
- [ ] テスト観点 or 具体テスト名記載
- [ ] Nextで必要なフォローアップが落ちていない

### ⏱️ タイムスタンプ記載ルール (NEW)
- すべてのChangelog冒頭 `_Created:` 行は **UTC** の実際の作成時刻を `date -u +%Y-%m-%dT%H:%M:%SZ` で取得した値に置き換えること。
- プレースホルダ(例: `00:00:00Z`)やローカルタイムは禁止。
- 再編集で内容を大幅更新する場合は `_Created:` は変更せず、必要なら本文 `## Change` に追記で差分説明。作成時刻は履歴指標として固定。
- コミットメッセージ先頭も同一生成コマンドのUTC ISO8601を利用し整合性を保つ。
- 自動化スクリプト導入時は同一フォーマッタ(UTC, 秒精度, 'Z' サフィックス)を必須条件とする。

このルールを守れない状況 (例: 緊急ホットフィックス) でも、事後5分以内に必ずChangelog補填すること。
