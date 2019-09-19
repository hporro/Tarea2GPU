//
// Created by heini on 19-09-2019.
//

#ifndef TAREA2_FIGURE_H
#define TAREA2_FIGURE_H


class Figure : public Model {
    virtual void draw(glm::mat4 projectionTransform, glm::mat4 viewTransform) = 0;
};


#endif //TAREA2_FIGURE_H
