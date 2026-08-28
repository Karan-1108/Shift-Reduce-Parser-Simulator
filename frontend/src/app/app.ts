import { Component } from '@angular/core';
import { ParserService, ParseResult } from './services/parser';

@Component({
  standalone: false,
  selector: 'app-root',
  templateUrl: './app.html',
  styleUrls: ['./app.css']
})
export class AppComponent {
  title = 'SLR(1) Parser Simulator';
  result: ParseResult | null = null;
  errorMessage: string = '';

  constructor(private parserService: ParserService) {}

  onParse(expression: string) {
    this.errorMessage = '';
    this.parserService.parseExpression(expression).subscribe({
      next: (res) => {
        this.result = res;
      },
      error: (err) => {
        this.errorMessage = 'Failed to parse expression or backend error occurred.';
        console.error(err);
      }
    });
  }
}