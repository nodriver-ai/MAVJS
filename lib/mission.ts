import * as turf from '@turf/turf';

export interface Camera {
  id: number,
  name: string,
  resolution: number,
  angle_of_view: number,
  img_resolution: ImgResolution,
  ts: number,
  te: number,
  overlap: number,
  theta: number,
  altitude: number
}

export interface MissionOptions {
  home: turf.Feature<turf.Point>,
  area: turf.Feature<turf.Polygon>,
  camera: Camera;
}

interface ImgResolution {
  x?: number,
  y?: number
}

interface CameraModel {
  projectionArea: ImgResolution,
  overlap: ImgResolution,
  ds: number,
  dw: number,
  vmax: number,
  altitude: number
}

interface AreaIndices {
  vstart: number,
  vscan: number,
  vfar: number,
  escan: number,
  num_nodes: number,
  mode: 0 | 1
}

export class Mission implements MissionOptions {
  home: turf.Feature<turf.Point>;
  area: turf.Feature<turf.Polygon>;
  camera: Camera;

  private camera_model: CameraModel;
  private indices: AreaIndices;

  private waypoints = [];

  constructor(options: MissionOptions) {
    this.home = options.home;
    this.area = options.area;
    this.camera = options.camera;

    this.compute_camera_model();
    this.compute_indices();
  }

  private compute_indices(): void {
    const vstart = turf.nearestPoint(this.home, turf.explode(this.area)).properties.featureIndex;
    const escan = this.compute_escan();
    const escan_segment = this.get_segment(escan)
    const vfar = this.compute_vfar(escan_segment);
    const num_nodes = turf.coordAll(this.area).length - 1

    let mode;
    let vscan = escan;
    if (vstart > vscan) {
      vscan += 1;
      mode = 0;
    }
    else {
      mode = 1;
    }

    this.indices = {
      vstart: vstart,
      vscan: vscan,
      vfar: vfar,
      escan: escan,
      num_nodes: num_nodes,
      mode: mode
    }
  }

  private compute_camera_model(): void {
    // Aspect ration
    const rho: number = this.camera.img_resolution.x / this.camera.img_resolution.y

    // h max
    const hmax: number = this.camera.img_resolution.x / (2 * this.camera.resolution * Math.tan(this.camera.angle_of_view / 2))
    const altitude = Math.min(this.camera.altitude, hmax)

    // Size of the projection area (Lx, Ly)
    const size_proj = 2 * altitude * Math.tan(this.camera.angle_of_view / 2)

    const projectionArea = {
      x: size_proj,
      y: size_proj / rho
    }

    // Resolution
    const resolution: number = this.camera.img_resolution.x / projectionArea.x

    const overlap = {
      x: projectionArea.x * (this.camera.overlap / 100),
      y: projectionArea.y * (this.camera.overlap / 100)
    }
    // Distance between the centers of two adjacent area along the wired direction
    const ds = projectionArea.x - overlap.x

    // Distance between the centers of two adjacent area along the path direction
    const dw = projectionArea.y - overlap.y

    // Maximum velocity of the drone
    const vmax = Math.min((projectionArea.y - overlap.y) / this.camera.ts, this.camera.theta / (resolution * this.camera.te))

    this.camera_model = {
      projectionArea: projectionArea,
      overlap: overlap,
      ds: ds,
      dw: dw,
      vmax: vmax,
      altitude: altitude
    }
  }

  private get_point(index: number): turf.Feature<turf.Point> {
    const points = turf.coordAll(turf.polygonToLine(this.area))
    return turf.point(points[index]);
  }

  private get_segment(index: number): turf.Feature<turf.LineString> {
    const segments = turf.lineSegment(this.area);
    return segments.features[index];
  }

  private compute_escan(): number {
    let segmentLenght = []
    turf.segmentEach(this.area, function (segment) {
      segmentLenght.push(turf.length(segment))
    });

    const maxLenght = Math.max(...segmentLenght);
    const segmentMaxLenghtIndex = segmentLenght.indexOf(maxLenght);
    return segmentMaxLenghtIndex;
  }

  private compute_vfar(segment: turf.Feature<turf.LineString>): number {
    let vertexDistance = [];
    turf.coordEach(this.area, function(vertex) {
      vertexDistance.push(turf.pointToLineDistance(vertex, segment))
    })

    const minDistance = Math.max(...vertexDistance);
    const vertexMinDistanceIndex = vertexDistance.indexOf(minDistance);

    return vertexMinDistanceIndex;
  }

  private compute_phase_1(point_i, point_j, point_next_i): void {
    const d = turf.distance(point_i, point_next_i) * 1000
    const nw = Math.ceil((d - this.camera_model.overlap.y) / this.camera_model.dw)
    //const ovy_ = ((nw * this.camera_model.projectionArea.y) - d) / (nw - 1)
    const dw_ = (d - this.camera_model.projectionArea.y) / (nw - 1)

    let x = turf.destination(point_i, this.camera_model.projectionArea.y / (2*1000), turf.bearing(point_i, point_next_i));
    x = turf.destination(x, this.camera_model.projectionArea.x / (2*1000),  turf.bearing(point_i, point_next_i) + point_j)
    this.waypoints.push(x)
    let prev_vertex = x;

    for(let j = 1; j < nw; j++) {
      let y = turf.destination(prev_vertex, dw_/1000, turf.bearing(point_i, point_next_i));
      this.waypoints.push(y);
      prev_vertex = y
    }
  }

  private compute_phase_2(clockwise: boolean) {
    const vscan_pre_point = this.get_point(this.indices.vscan);

    let vscan_point;
    if (clockwise) {
      vscan_point = this.get_point(this.indices.vscan - 1)
    }
    else {
      vscan_point = this.get_point(this.indices.vscan + 1)
    }

    const vfar_point = this.get_point(this.indices.vfar);
    const escan_segment = this.get_segment(this.indices.escan)

    const dfs = turf.pointToLineDistance(vfar_point, this.get_segment(this.indices.escan)) * 1000;

    let ns = Math.ceil((dfs - this.camera_model.overlap.x) / this.camera_model.ds)
    if (ns % 2) {
      ns += 1;
    }
    //const ovx_ = ((ns * this.camera_model.projectionArea.x) - dfs) / (ns - 1)
    const ds_ = (dfs - this.camera_model.projectionArea.x) / (ns - 1)

    for (let i = 0; i < ns; i++) {
      const bbox = turf.bboxPolygon(turf.bbox(this.area))
      const len = turf.length(turf.lineSegment(bbox).features[0])

      let p1, p2, vleftright, intersections, start_point, d;;
      if (clockwise) {
        p1 = turf.destination(escan_segment.geometry.coordinates[0], len/2, turf.bearing(vscan_pre_point, vscan_point))
        p2 = turf.destination(escan_segment.geometry.coordinates[1], -len/2, turf.bearing(vscan_pre_point, vscan_point))
        vleftright = turf.transformTranslate(turf.lineString([p1.geometry.coordinates, p2.geometry.coordinates]), (i* ds_)/1000 + (this.camera_model.projectionArea.x / (2 * 1000)), turf.bearing(vscan_pre_point, vscan_point) + 90);
        intersections = turf.lineIntersect(vleftright, turf.polygonToLine(this.area));

        if (turf.distance(intersections.features[1], vscan_pre_point) > turf.distance(intersections.features[0], vscan_pre_point)) {
          const gamma = turf.bearing(intersections.features[0], intersections.features[1])
          start_point = turf.destination(intersections.features[0], this.camera_model.ds / 1000, gamma)
          d = turf.distance(start_point, intersections.features[1]) * 1000
        } else {
          const gamma = turf.bearing(intersections.features[1], intersections.features[0])
          start_point = turf.destination(intersections.features[1], this.camera_model.ds / 1000, gamma)
          d = turf.distance(start_point, intersections.features[0]) * 1000
        }

      }
      else {
        p1 = turf.destination(escan_segment.geometry.coordinates[0], -len/2, turf.bearing(vscan_pre_point, vscan_point))
        p2 = turf.destination(escan_segment.geometry.coordinates[1], len/2, turf.bearing(vscan_pre_point, vscan_point))
        vleftright = turf.transformTranslate(turf.lineString([p1.geometry.coordinates, p2.geometry.coordinates]), (i * ds_)/1000 + (this.camera_model.projectionArea.x / (2 * 1000)), turf.bearing(vscan_pre_point, vscan_point) - 90);
        intersections = turf.lineIntersect(vleftright, turf.polygonToLine(this.area));

        if (turf.distance(intersections.features[0], vscan_pre_point) < turf.distance(intersections.features[1], vscan_pre_point)) {
          const gamma = turf.bearing(intersections.features[0], intersections.features[1])
          start_point = turf.destination(intersections.features[0], this.camera_model.ds / 1000, gamma)
          d = turf.distance(start_point, intersections.features[1]) * 1000
        } else {
          const gamma = turf.bearing(intersections.features[1], intersections.features[0])
          start_point = turf.destination(intersections.features[1], this.camera_model.ds / 1000, gamma)
          d = turf.distance(start_point, intersections.features[0]) * 1000
        }

      }

      const nw = Math.ceil((d - this.camera_model.overlap.y) / this.camera_model.dw)
      const dw_ = (d - this.camera_model.projectionArea.y) / (nw - 1)
      if (dw_ > 0) {
        let x = turf.destination(start_point, this.camera_model.projectionArea.y / (2* 1000), turf.bearing(vscan_pre_point, vscan_point));
        this.waypoints.push(x)

        let prev_vertex = x;
        for(let j = 1; j < nw; j++) {
          let y = turf.destination(prev_vertex, dw_/1000, turf.bearing(vscan_pre_point, vscan_point));
          this.waypoints.push(y);
          prev_vertex = y
        }
      }
      else {
        this.waypoints.push(start_point);
      }

    }

  }

  private compute_phase_3(clockwise: boolean): void {
    if (clockwise) {
      if (this.indices.vfar > this.indices.vstart) {
        for (let i = this.indices.vfar; i > this.indices.vstart; i--) {
          const point_i = this.get_point(i);
          const point_j = 90;
          const point_next_i = this.get_point(i - 1)
          this.compute_phase_1(point_i, point_j, point_next_i)
        }
      }

      if (this.indices.vfar < this.indices.vstart) {
        for (let i = this.indices.vfar; i > 0; i--) {
          const point_i = this.get_point(i);
          const point_j = 90;
          const point_next_i = this.get_point(i - 1)
          this.compute_phase_1(point_i, point_j, point_next_i)
        }

        for (let i = this.indices.num_nodes; i < this.indices.vstart; i--) {
          const point_i = this.get_point(i);
          const point_j = 90;
          const point_next_i = this.get_point(i - 1)
          this.compute_phase_1(point_i, point_j, point_next_i)
        }
      }
    }
    else {
      if (this.indices.vfar < this.indices.vstart) {
        for (let i = this.indices.vfar; i < this.indices.vstart; i++) {
          const point_i = this.get_point(i);
          const point_j = -90;
          const point_next_i = this.get_point(i + 1)
          this.compute_phase_1(point_i, point_j, point_next_i)
        }
      }

      if (this.indices.vfar > this.indices.vstart) {
        for (let i = this.indices.vfar; i < this.indices.num_nodes; i++) {
          const point_i = this.get_point(i);
          const point_j = -90;

          let i_ = i + 1;
          if(i_ === this.indices.num_nodes) {
            i_ = 0
          }
          const point_next_i = this.get_point(i_)
          this.compute_phase_1(point_i, point_j, point_next_i)
        }
      }

      for (let i = 0; i < this.indices.vstart; i++) {
        const point_i = this.get_point(i);
        const point_j = -90;
        const point_next_i = this.get_point(i + 1)
        this.compute_phase_1(point_i, point_j, point_next_i)
      }
    }
  }

  generate() {
    switch(this.indices.mode) {
       case 0: {
         for (let i = this.indices.vstart; i > this.indices.vscan; i--) {
           const point_i = this.get_point(i);
           const point_j = 90;
           const point_next_i = this.get_point(i - 1)
           this.compute_phase_1(point_i, point_j, point_next_i)
         }
         this.compute_phase_2(true)
         this.compute_phase_3(true);
         break;
       }
       case 1: {
         for (let i = this.indices.vstart; i < this.indices.vscan; i++) {
           const point_i = this.get_point(i);
           const point_j = -90;
           const point_next_i = this.get_point(i + 1)
           this.compute_phase_1(point_i, point_j, point_next_i)
         }
         this.compute_phase_2(false);
         this.compute_phase_3(false);
         break;
       }
    }

    return this.waypoints;
  }

}
