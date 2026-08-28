import { Component, Input } from '@angular/core';
import { SymbolEntry } from '../../services/parser';

@Component({
  standalone: false,
  selector: 'app-symbol-table',
  template: `
    <div *ngIf="symbols.length > 0" class="section">
      <h3>Symbol Table</h3>
      <table class="styled-table">
        <thead>
          <tr><th>Identifier</th><th>Data Type</th><th>Occurrence Order</th></tr>
        </thead>
        <tbody>
          <tr *ngFor="let sym of symbols">
            <td><code>{{ sym.name }}</code></td>
            <td>{{ sym.type }}</td>
            <td>{{ sym.order }}</td>
          </tr>
        </tbody>
      </table>
    </div>
  `,
  styles: [`
    .styled-table { width: 100%; border-collapse: collapse; }
    .styled-table th, .styled-table td { border: 1px solid #ddd; padding: 8px; text-align: left; }
    .styled-table th { background-color: #f4f4f4; }
  `]
})
export class SymbolTableComponent {
  @Input() symbols: SymbolEntry[] = [];
}