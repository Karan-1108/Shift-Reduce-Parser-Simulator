import { Component, Input } from '@angular/core';
import { ParseStep } from '../../services/parser';

@Component({
  standalone: false,
  selector: 'app-trace-table',
  template: `
    <div *ngIf="trace.length > 0" class="section">
      <h3>SLR(1) Parsing Step-by-Step Trace</h3>
      <table class="styled-table">
        <thead>
          <tr>
            <th>Step</th>
            <th>Parser State Stack</th>
            <th>Input Buffer</th>
            <th>Action Taken</th>
          </tr>
        </thead>
        <tbody>
          <tr *ngFor="let row of trace" 
              [class.shift-row]="row.action.includes('Shift')"
              [class.reduce-row]="row.action.includes('Reduce')"
              [class.accept-row]="row.action.includes('Accept')">
            <td>{{ row.step }}</td>
            <td><code>{{ row.stack }}</code></td>
            <td><code>{{ row.buffer }}</code></td>
            <td><strong>{{ row.action }}</strong></td>
          </tr>
        </tbody>
      </table>
    </div>
  `,
  styles: [`
    .section { margin-top: 25px; }
    .styled-table { width: 100%; border-collapse: collapse; font-family: sans-serif; }
    .styled-table th, .styled-table td { border: 1px solid #ddd; padding: 10px; text-align: left; }
    .styled-table th { background-color: #f4f4f4; }
    .shift-row { background-color: #e8f4f8; }
    .reduce-row { background-color: #fff3cd; }
    .accept-row { background-color: #d4edda; }
  `]
})
export class TraceTableComponent {
  @Input() trace: ParseStep[] = [];
}