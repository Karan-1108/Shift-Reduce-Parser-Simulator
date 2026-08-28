import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

export interface ParseStep {
  step: number;
  stack: string;
  buffer: string;
  action: string;
}

export interface SymbolEntry {
  name: string;
  type: string;
  order: number;
}

export interface ParseResult {
  success: boolean;
  trace: ParseStep[];
  symbols: SymbolEntry[];
  tac: string[];
  benchmark: {
    slrTimeMs: number;
    rdTimeMs: number;
    rdPeakStackDepth: number;
  };
}

@Injectable({
  providedIn: 'root'
})
export class ParserService {
  private apiUrl = 'http://localhost:3000/api/parse';

  constructor(private http: HttpClient) {}

  parseExpression(expression: string): Observable<ParseResult> {
    return this.http.post<ParseResult>(this.apiUrl, { expression });
  }
}