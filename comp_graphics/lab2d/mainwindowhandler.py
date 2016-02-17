from random import random
from gi.repository import Gtk

from graphutils import Transformation, Polygon, Viewport, Vector
from drawer import Drawer

import math


class MainWindowHandler:
    def __init__(self):
        self._init_polygons()
        self._init_ui()

    def _init_ui(self):
        self.builder = Gtk.Builder()
        self.builder.add_from_file("mainwindow.glade")
        self.builder.connect_signals(self)

        self.win = self.builder.get_object("main_window")
        self.xmin_spin = self.builder.get_object("xmin_spin")
        self.xmax_spin = self.builder.get_object("xmax_spin")
        self.ymin_spin = self.builder.get_object("ymin_spin")
        self.ymax_spin = self.builder.get_object("ymax_spin")

    def _init_polygons(self):
        self.polys = []
        poly = Polygon([
            Vector(1, 1),
            Vector(2, 1.5),
            Vector(3, -1),
            Vector(0.5, -0.1),
        ])
        self.polys.append(poly)

        transformations = [
            Transformation.rotate(math.pi, Vector(1, 1)),
            Transformation.scale(2, 2),
        ]

        for transform in transformations:
            self.polys.append(poly.transform(transform))

    def run(self):
        self.win.show_all()
        Gtk.main()

    def on_window_delete(self, *args):
        Gtk.main_quit(*args)

    def on_drawing_area_draw(self, da, ctx):
        viewport = Viewport(self.xmin_spin.get_value(),
                            self.xmax_spin.get_value(),
                            self.ymin_spin.get_value(),
                            self.ymax_spin.get_value())
        ctx.set_line_width(1)

        drw = Drawer(viewport, da, ctx)
        drw.draw_axes()

        for poly in self.polys:
            drw.draw_polygon(poly)
            ctx.set_source_rgb(random(),
                               random(),
                               random())

    def on_spin_value_changed(self, obj):
        self.win.queue_draw()
