import { Component, Input } from '@angular/core';

@Component({
  standalone: false,
  selector: 'app-benchmark',
  template: `
    <div *ngIf="data" class="benchmark-card">
      <h3>Parser Performance Comparison</h3>
      <div class="metrics-grid">
        <div class="metric"><span class="label">SLR(1) Execution Time:</span> <span class="val">{{ data.slrTimeMs }} ms</span></div>
        <div class="metric"><span class="label">Recursive Descent Time:</span> <span class="val">{{ data.rdTimeMs }} ms</span></div>
        <div class="metric"><span class="label">RD Peak Call Stack Depth:</span> <span class="val">{{ data.rdPeakStackDepth }}</span></div>
      </div>
    </div>
  `,
  styles: [`
    .benchmark-card { background: #f8f9fa; padding: 15px; border-radius: 6px; border: 1px solid #e9ecef; margin-top: 15px; }
    .metrics-grid { display: flex; gap: 20px; margin-top: 10px; }
    .metric { background: white; padding: 10px 15px; border-radius: 4px; border: 1px solid #ced4da; }
    .label { font-size: 13px; color: #6c757d; display: block; }
    .val { font-size: 18px; font-weight: bold; color: #212529; }
  `]
})
export class BenchmarkComponent {
  @Input() data: { slrTimeMs: number; rdTimeMs: number; rdPeakStackDepth: number } | null = null;
}