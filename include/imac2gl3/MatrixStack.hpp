#ifndef _IMAC2GL3_MATRIXSTACK_HPP_
#define _IMAC2GL3_MATRIXSTACK_HPP_

#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MatrixStack{
    public:
        MatrixStack();
        ~MatrixStack();

        void push();
        void pop();

        void mult(const glm::mat4& m);

        const glm::mat4& top() const;

        void set(const glm::mat4& m);

        void scale(const glm::vec3& s);
        void translate(const glm::vec3& t);
        void rotate(float degrees, const glm::vec3& r);

    private:
        std::stack<glm::mat4> m_Stack;
};

#endif
