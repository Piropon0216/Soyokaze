# Start StockResolver TDD
_Created: 2025-10-04T02:10:00Z_

## Context
- Start TDD cycle for "銘柄名 -> 証券コード -> Yahoo URL" feature. Initial tests added (red).

## Change
- Add failing unit tests: `tests/testcode/stock/StockResolverTest.cpp`, `tests/testcode/stock/SymbolUrlBuilderTest.cpp`.

## Impact / Risk
- Tests currently fail (intended). No production code changed yet.

## Test
- Run UnitTest executable after implementing feature.

## Next
- Implement minimal StockResolver and SymbolUrlBuilder with hardcoded small map, re-run tests.
