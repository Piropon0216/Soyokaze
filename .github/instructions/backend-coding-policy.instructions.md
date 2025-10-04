# Backend Coding Policy Instructions

## Goals
一貫性・高可読性・低リスクリリースを支える Python/TS バックエンド実装規約。

## Language / FW Versions
- Python 3.11
- Node.js LTS (>=20)
- Azure Functions v4

## Style
- Python: black + isort + flake8 (E,F,W) / 120 cols
- TS: eslint (airbnb + project rules) + prettier (printWidth 100)

## Modules Layout
```
src/agenticrag-functions/
  common/    # shared pure helpers
  adapters/  # I/O (API, storage)
  agents/    # domain agents
  orchestration/ # planner, fan-out
```

## Patterns
| Rule | Rationale |
|------|-----------|
| No global mutable state | 並列安全 & テスト容易 |
| Pure functions for calc | 再利用 + property testing |
| Dataclass (frozen) for DTO | 不変性確保 |
| Explicit error types | 失敗経路の明示化 |

## Naming
- Functions: verb_object (`fetch_quotes`, `compute_change_rate`)
- Modules: snake_case domain oriented
- Env Vars: UPPER_SNAKE (`MARKET_API_BASE_URL`)

## Error Handling
```python
try:
    data = fetch_quotes(symbols)
except ExternalAPIError as e:
    logger.warning("quote_fetch_failed", extra={"err": str(e)})
    return degraded_result()
```

## Performance Practices
- Avoid N+1 HTTP: batch endpoints if available
- Vectorizable calc: prefer numpy/polars if hotspot (>5k rows)

## Security
- Never log secrets / PII
- Input validation before external calls

## Dependency Policy
- Pin direct deps (requirements.txt == locked versions)
- Quarterly review transitive vulnerabilities

## Review Checklist (Subset)
- [ ] 関数docstring + 型ヒント
- [ ] 例外分類適切
- [ ] ログに correlation id 付与
- [ ] テスト(正常/異常/境界) 追加
- [ ] Markdown link check パス (`npm run check:links`)
- [ ] ブランチ命名/コミット prefix ルール遵守

## References
- docs/agent_handoff_lessons.md
