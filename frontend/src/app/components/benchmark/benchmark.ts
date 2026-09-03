import { Component, Input } from '@angular/core';

@Component({
  standalone: false,
  selector: 'app-benchmark',
  templateUrl: './benchmark.html',
  styleUrls: ['./benchmark.css']
})
export class BenchmarkComponent {
  @Input() data: { slrTimeMs: number; rdTimeMs: number; rdPeakStackDepth: number } | null = null;
}