import { Component, Input } from '@angular/core';
import { ParseStep } from '../../services/parser';

@Component({
  standalone: false,
  selector: 'app-trace-table',
  templateUrl: './trace-table.html',
  styleUrls: ['./trace-table.css']
})
export class TraceTableComponent {
  @Input() trace: ParseStep[] = [];
}