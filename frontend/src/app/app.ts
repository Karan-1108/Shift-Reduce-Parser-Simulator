import { Component } from '@angular/core';
import { HttpErrorResponse } from '@angular/common/http';
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
  isParsing = false;
  isAboutOpen = false;

  constructor(private parserService: ParserService) {}

  openAbout(): void {
    this.isAboutOpen = true;
  }

  closeAbout(): void {
    this.isAboutOpen = false;
  }

  onParse(expression: string) {
    this.errorMessage = '';
    this.isParsing = true;
    this.parserService.parseExpression(expression).subscribe({
      next: (res) => {
        this.result = res;
        this.isParsing = false;
      },
      error: (err) => {
        this.isParsing = false;
        this.errorMessage = this.getErrorMessage(err);
        console.error(err);
      }
    });
  }

  private getErrorMessage(error: unknown): string {
    if (error instanceof HttpErrorResponse) {
      if (error.status === 0) {
        return 'Cannot connect to the backend. Start server.js on http://localhost:3000.';
      }

      const backendMessage = typeof error.error?.error === 'string'
        ? error.error.error
        : '';
      return backendMessage || `Backend error (${error.status}).`;
    }

    return 'An unexpected error occurred while parsing.';
  }
}