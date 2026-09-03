import { Component, Input } from '@angular/core';
import { SymbolEntry } from '../../services/parser';

@Component({
  standalone: false,
  selector: 'app-symbol-table',
  templateUrl: './symbol-table.html',
  styleUrls: ['./symbol-table.css']
})
export class SymbolTableComponent {
  @Input() symbols: SymbolEntry[] = [];
}