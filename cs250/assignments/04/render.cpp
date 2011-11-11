// test

#include "render.hpp"

#include <algorithm>
#include <iostream>
#include <functional>
//#include <array>
#include "transformations.hpp"
#include "Utilities.h"

RenderWorld Renderer;

#ifdef WIN32
#undef min
#undef max
#endif // WIN32

namespace
{
	void ApplyToTriangleVertices(Triangle& to_edit, std::function<void(Point4&)> fun)
	{
		fun(to_edit.p0);
		fun(to_edit.p1);
		fun(to_edit.p2);
	}

    int Round(float to_round)
	{
		return static_cast<int>(to_round + 0.5f);
	}

	float Clamp(float to_clamp, float lower, float upper)
	{
		return(std::min(upper, std::max(lower, to_clamp)));
	}

	Point4 RenormalizeW(Point4 point)
	{
		point.x /= point.w;
		point.y /= point.w;
		point.z /= point.w;
		point.w /= point.w;

		return(point);
	}

	float fequal(float a, float b)
	{
		return (std::fabs(a - b) < EPSILON);
	}

    float safe_divide(float a, float b)
    {
        if (fequal(b, 0.0f))
        {
            return(0.0f);
        }

        return(a / b);
    }

    // TODO: LERP the colors, but not important right now.
    template<bool MoreHorizontal>
        void DrawLine(Point4 p0, Point4 p1, Vector4 c0, Vector4 c1);

    template<>
    void DrawLine<true>(Point4 p0, Point4 p1, Vector4 c0, Vector4 /* c1 */)
	{
        int y_step = (p1.y < p0.y) ? -1 : 1;

        int current_x = p0.x;
        int current_y = p0.y;

        if (y_step == 1)
            std::swap(p0.y, p1.y);

		int a = p1.y - p0.y;
        int b = p1.x - p0.x;
        // int c = end_x * start_y - end_y * start_x;

        int dp = 2 * a + b;

        int steps = p1.x - p0.x; // Number of iterations.

        // Draw initial pixel.
        FrameBuffer::SetPixel(current_x, current_y, 0.0f, c0.r, c0.g, c0.b);

        while (steps--)
        {
            if (dp < 0)
            {
                current_y += y_step;

                dp += a + b;
            }
            else
            {
                dp += a;
            }

            ++current_x;
            FrameBuffer::SetPixel(current_x, current_y, 0.0f, c0.r, c0.g, c0.b);
        }
	}
	template<>
	void DrawLine<false>(Point4 p0, Point4 p1, Vector4 c0, Vector4 /* c1 */)
	{
		int x_step = (p1.x < p0.x) ? -1 : 1;

        int current_x = p0.x;
        int current_y = p0.y;

        if (x_step == 1)
            std::swap(p0.x, p1.x);

		int a = p1.x - p0.x;
        int b = p1.y - p0.y;
        // int c = end_y * start_x - end_x * start_y;

        int dp = 2 * a + b;

        int steps = p1.y - p0.y; // Number of iterations.

        // Draw initial pixel.
        FrameBuffer::SetPixel(current_x, current_y, 0.0f, c0.r, c0.g, c0.b);

        while (steps--)
        {
            if (dp < 0)
            {
                current_x += x_step;

                dp += a + b;
            }
            else
            {
                dp += a;
            }

            ++current_y;
            FrameBuffer::SetPixel(current_x, current_y, 0.0f, c0.r, c0.g, c0.b);
        }
    }

    struct HalfTriangleRasterizer
    {
        Vector4 c0, c1, c2;
        Vector4 uv0, uv1, uv2;
        float current_y;
        float x_left, x_right;
		float z_left, z_right;
		float dz_left, dz_right;
        Vector4 color_left, color_right;
        Vector4 dc_left, dc_right;
        Vector4 uv_left, uv_right;
        Vector4 duv_left, duv_right;
        float slope_left, slope_right;

        std::vector<unsigned char> texture;
        int tex_height, tex_width, bpp;
        TextureMode mode;

        void rasterize(float limit)
        {
			//std::cout << "Z_left is " << z_left << std::endl;
			//std::cout << "z_right is " << z_right << std::endl;
            while (current_y < std::ceil(limit))
            {
                Vector4 temp = color_left;
			    float dr = static_cast<float>(color_right.r - color_left.r) / (x_right - x_left);
                float dg = static_cast<float>(color_right.g - color_left.g) / (x_right - x_left);
                float db = static_cast<float>(color_right.b - color_left.b) / (x_right - x_left);

			    Vector4 temp_uv = uv_left;
			    Vector4 temp_duv = 1.0f / (x_right - x_left) * (uv_right + -1 * uv_left);

				float temp_z = z_left;
				float temp_dz = (z_right - z_left) / (x_right - x_left);

                for (int i = std::ceil(x_left); i <= std::ceil(x_right)-1; ++i)
                {
                    //FrameBuffer::SetPixel(i, current_y, temp.r, temp.g, temp.b);
				    Vector4 to_set;
				    int u = Clamp(Round(temp_uv.x * tex_width-1), 0, tex_width-1);
				    int v = Clamp(Round(temp_uv.y * tex_height-1), 0, tex_height-1);
				    switch (mode)
				    {
					    case VERTEX:
						    to_set.r = temp.r;
						    to_set.g = temp.g;
						    to_set.b = temp.b;
						    break;
					    case DECAL:
						    to_set.r = temp.r + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 0] - temp.r);
						    to_set.g = temp.g + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 1] - temp.g);
						    to_set.b = temp.b + (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 3]) * (texture[v * tex_height * bpp + u * bpp + 2] - temp.b);
						    break;
					    case MODULATE:
						    to_set.r = (1.0f / 255.0f * temp.r) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 0]) * 255;
						    to_set.g = (1.0f / 255.0f * temp.g) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 1]) * 255;
						    to_set.b = (1.0f / 255.0f * temp.b) * (1.0f / 255.0f * texture[v * tex_height * bpp + u * bpp + 2]) * 255;
						    break;
					    case REPLACE:
						    to_set.r = texture[v * tex_height * bpp + u * bpp + 0];
						    to_set.g = texture[v * tex_height * bpp + u * bpp + 1];
						    to_set.b = texture[v * tex_height * bpp + u * bpp + 2];
						    break;
				    }

					//std::cout << "Temp z is: " << temp_z << std::endl;
				    FrameBuffer::SetPixel(i, current_y, temp_z, to_set.r, to_set.g, to_set.b);
                    temp.r += dr;
                    temp.g += dg;
                    temp.b += db;

				    temp_uv += temp_duv;
					temp_z += temp_dz;
                }

                color_left.r += dc_left.r;
                color_left.g += dc_left.g;
                color_left.b += dc_left.b;

                color_right.r += dc_right.r;
                color_right.g += dc_right.g;
                color_right.b += dc_right.b;

			    uv_left += duv_left;
			    uv_right += duv_right;

                x_left += slope_left;
                x_right += slope_right;
				
				z_left += dz_left;
				z_right += dz_right;

                ++current_y;
            }
        }
    };
}

template<typename T>
struct Lerper
{
	T start_value;
	T end_value;
	T current_value;
	T delta;

	Lerper& setUp(T new_start, T new_end, unsigned steps)
	{
		start_value = new_start;
		end_value = new_end;

		delta = (end_value - start_value) / steps;

		current_value = start_value;
	}

	Lerper& operator++()
	{
		current_value += delta;
		return(*this);
	}
};

bool ArrangeTriangle(Triangle& arranged, const Triangle& to_draw)
{
    bool mid_left;

    if (to_draw.p0.y < to_draw.p1.y) // 4, 5, 6
    {
        //std::cout << "4, 5, 6" << std::endl;
        if (to_draw.p2.y <= to_draw.p0.y) // 4
        {
            arranged.p0 = to_draw.p2;
            arranged.p1 = to_draw.p0;
            arranged.p2 = to_draw.p1;

            arranged.c0 = to_draw.c2;
            arranged.c1 = to_draw.c0;
            arranged.c2 = to_draw.c1;

	    	arranged.t0 = to_draw.t2;
		    arranged.t1 = to_draw.t0;
			arranged.t2 = to_draw.t1;

            mid_left = true;
        }
        else // 5, 6
        {
            //std::cout << "5, 6" << std::endl;
            arranged.p0 = to_draw.p0;
            arranged.c0 = to_draw.c0;
		    arranged.t0 = to_draw.t0;

            if (to_draw.p1.y < to_draw.p2.y) // 5
            {
                //std::cout << "5" << std::endl;
                arranged.p1 = to_draw.p1;
                arranged.p2 = to_draw.p2;

                arranged.c1 = to_draw.c1;
                arranged.c2 = to_draw.c2;

			    arranged.t1 = to_draw.t1;
				arranged.t2 = to_draw.t2;

                mid_left = true;
            }
            else // 6
            {
                arranged.p1 = to_draw.p2;
                arranged.p2 = to_draw.p1;

                arranged.c1 = to_draw.c2;
                arranged.c2 = to_draw.c1;

			    arranged.t1 = to_draw.t2;
				arranged.t2 = to_draw.t1;

                mid_left = false;
            }
        }
    }
    else // 1, 2, 3
    {
        //std::cout << "1, 2, 3" << std::endl;
        if (to_draw.p2.y < to_draw.p1.y) // 2
        {
            //std::cout << "2" << std::endl;
            arranged.p0 = to_draw.p2;
            arranged.p1 = to_draw.p1;
            arranged.p2 = to_draw.p0;

            arranged.c0 = to_draw.c2;
            arranged.c1 = to_draw.c1;
            arranged.c2 = to_draw.c0;

			arranged.t0 = to_draw.t2;
			arranged.t1 = to_draw.t1;
			arranged.t2 = to_draw.t1;

            mid_left = false;
        }
        else // 1, 3
        {
            //std::cout << "1, 3" << std::endl;
            arranged.p0 = to_draw.p1;
            arranged.c0 = to_draw.c1;
		    arranged.t0 = to_draw.t1;

            if (to_draw.p0.y < to_draw.p2.y) // 3
            {
                //std::cout << "3" << std::endl;
                arranged.p1 = to_draw.p0;
                arranged.p2 = to_draw.p2;

                arranged.c1 = to_draw.c0;
                arranged.c2 = to_draw.c2;

				arranged.t1 = to_draw.t0;
				arranged.t2 = to_draw.t2;

                mid_left = false;
            }
            else // 1
            {
                arranged.p1 = to_draw.p2;
                arranged.p2 = to_draw.p0;

                arranged.c1 = to_draw.c2;
                arranged.c2 = to_draw.c0;

				arranged.t1 = to_draw.t2;
				arranged.t2 = to_draw.t0;

                mid_left = true;
            }
        }
    }

    return(mid_left);
}

void RenderLine(Point4 p0, Point4 p1, Vector4 c0, Vector4 c1)
{
	bool more_horizontal = abs(p1.x - p0.x) > abs(p1.y - p0.y);

	// Make sure the start point is always "lower" on the iterating factor than the end.
	if (more_horizontal)
	{		
		if (p1.x < p0.x) // Bah, wrong order, swap!
		{
			std::swap(p0, p1);
            std::swap(c0, c1);
		}
		
		DrawLine<true>(p0, p1, c0, c1);
	}
	else
	{		
		if (p1.y < p0.y) // Bah, wrong order, swap!
		{
			std::swap(p0, p1);
			std::swap(c0, c1);
		}
		
		DrawLine<false>(p0, p1, c0, c1);
	}

}

void RenderWireframeTriangle(const Triangle& to_draw)
{
    RenderLine(to_draw.p0, to_draw.p1, to_draw.c0, to_draw.c1);
    RenderLine(to_draw.p1, to_draw.p2, to_draw.c1, to_draw.c2);
    RenderLine(to_draw.p0, to_draw.p2, to_draw.c0, to_draw.c2);
}

struct WireframeTriangleRasterizer
{
	void Rasterize(const Triangle& to_draw)
	{
		RenderLine(to_draw.p0, to_draw.p1, to_draw.c0, to_draw.c1);
		RenderLine(to_draw.p1, to_draw.p2, to_draw.c1, to_draw.c2);
		RenderLine(to_draw.p0, to_draw.p2, to_draw.c0, to_draw.c2);
	}
};

void RenderWorld::addDrawable(Triangle new_triangle)
{
    myDrawList.push_back(new_triangle);
}

struct NoCulling
{
    bool CullingTest(const Triangle&)
    {
        return(true);
    }
};

struct NoBackfaceRemoval
{
    bool BackfaceTest(const Triangle&)
    {
		//std::cout << "No backface removal performed." << std::endl;
        return(true);
    }
};

struct NoClipping
{
    void Clip(std::vector<Triangle>& output, Triangle& to_clip)
    {
		//std::cout << "No clipping performed." << std::endl;
        output.push_back(to_clip);
		//std::cout << "Ouput contains " << output.size() << " triangles." << std::endl;
    }
};

struct StandardViewportPolicy
{
	Matrix4 GetViewportMatrix() const
	{
		return(mat4::translate(Vector4(WIDTH/2, HEIGHT/2, 0.0f)) * mat4::scale(Vector4(WIDTH, HEIGHT, 1.0f)));
	}
};

template
    <
	typename ViewportPolicy,
    typename ProjectionPolicy,
    typename CameraPolicy,
    typename DepthTestPolicy,
    typename TriangleRasterizePolicy,
    typename CullingPolicy = NoCulling,
    typename BackfaceRemovalPolicy = NoBackfaceRemoval,
    typename ClippingPolicy = NoClipping
    >
struct RenderPipeline :
	public ViewportPolicy, public ProjectionPolicy, public CameraPolicy,
    public DepthTestPolicy, public TriangleRasterizePolicy,
    public CullingPolicy, public BackfaceRemovalPolicy, public ClippingPolicy
{
    // Transformation matrix policies.
	using ViewportPolicy::GetViewportMatrix;
    using ProjectionPolicy::GetProjectionMatrix;
    using CameraPolicy::GetCameraMatrix;

    // Depth test policies.
    using DepthTestPolicy::CalculateDepth;
	using DepthTestPolicy::DepthReturnType;

    // Triangle rasterization method.
    using TriangleRasterizePolicy::Rasterize;

    // Optimization policies.
    // These return false if the triangle should be removed.
    using CullingPolicy::CullingTest;
    using BackfaceRemovalPolicy::BackfaceTest;
    using ClippingPolicy::Clip;

    /* Give this a triangle in worldspace coordinates.
     *
     * The triangle is only drawn if it's in CCW vertex order.
     */
    void operator()(Triangle to_draw)
    {
        if (!CullingTest(to_draw))
            return;

        if (!BackfaceTest(to_draw))
            return;

        // TODO: Worldspace clipping here.
        // Clipping may result in multiple triangles.
        // How to handle? Return triangle fan vertices to here?
        // Probably better to return list of Triangle types since it carries
        // vertex information.
        std::vector<Triangle> clipped_triangles(0);
        
        // Ouputs new triangles to the first argument.
        Clip(clipped_triangles, to_draw);

		//std::cout << "Confirming size of clipped_triangles: " << clipped_triangles.size() << std::endl;

        for (auto it = clipped_triangles.begin();
                it != clipped_triangles.end();
                ++it)
        {
			Matrix4 temp = GetCameraMatrix();
			auto multiply_vertex_by_temp = [&temp](Point4& x){ x = temp * x; };
            // First, transform the triangle into camera space.
			ApplyToTriangleVertices(*it, multiply_vertex_by_temp);

            // Now, get normalized depth to repack.
            // Calculated based on camera space values.
			//std::array<DepthReturnType, 3> normal_z;
			//std::for_each(normal_z.begin(), normal.z_end(), [](DepthReturnType& x){x = CalculateDepth(x);});
            auto z0 = CalculateDepth(it->p0.z);
            auto z1 = CalculateDepth(it->p1.z);
            auto z2 = CalculateDepth(it->p2.z);

            // Project the triangle.
			temp = GetProjectionMatrix();
			ApplyToTriangleVertices(*it, multiply_vertex_by_temp);

			// Renormalize the w.
			ApplyToTriangleVertices(*it, [](Point4& x){ x = RenormalizeW(x); });

			// Viewport transformation, should not modify the z.
			temp = GetViewportMatrix();
			ApplyToTriangleVertices(*it, multiply_vertex_by_temp);

			// Repack the z value into the vertices.
			//std::for_each(normal_z.begin(), normal_z.end(), [](DepthReturnType& x){});
			//std::cout << "z: " << z0 << ' ' << z1 << ' ' << z2 << std::endl;
            it->p0.z = z0;
            it->p1.z = z1;
            it->p2.z = z2;

			//std::cout << "Triangle z: " << it->p0.z << ' ' << it->p1.z << ' ' << it->p2.z << std::endl;

            // Rasterize the actual triangle.
            // Rasterizer needs to do the depth test on its own.
            Rasterize(*it);
        }
		//std::cout << "Rasterization complete." << std::endl;
    }
};

struct StandardProjectionPolicy
{
	Matrix4 GetProjectionMatrix() const
	{
		// TODO: Hardcoded, fix this!
		float left = -160.0f;
		float right = 160.0f;
		float top = 120.0f;
		float bottom = -120.0f;
		float near = 36.0f;
		float far = 500.0f;
		float focus = 25.0f;

		Matrix4 to_return;
		to_return.Zero();
#if 0
		to_return.m[0][0] = 2.0f*near/(right - left);
		to_return.m[1][1] = 2.0f*near/(top - bottom);
		to_return.m[2][2] = -(far + near) / (far - near);

		to_return.m[0][2] = (right + left) / (right - left);
		to_return.m[1][2] = (top + bottom) / (top - bottom);
        to_return.m[3][2] = -1.0f;
        to_return.m[2][3] = -(2.0f * far * near) / (far - near);
#else
		to_return.m[0][0] = focus / ((right - left) / 2);
		to_return.m[1][1] = focus / ((top - bottom) / 2);
		to_return.m[2][2] = -(far + near) / (far - near);
		to_return.m[2][3] = -2.0f * near * far / (far - near);
		to_return.m[3][2] = -1.0f;
#endif

		return(to_return);
	}
};

void RenderWorld::setCameraMatrix(Matrix4 new_camera)
{
	myCamera = new_camera;
}

Matrix4 RenderWorld::getCameraMatrix() const
{
	return(myCamera);
}

struct StandardCameraPolicy
{
	Matrix4 GetCameraMatrix() const
	{
		return(Renderer.getCameraMatrix());
	}
};

struct DepthTester
{
	typedef float DepthReturnType;
	DepthReturnType CalculateDepth(float old_z)
	{
		// TODO: Don't hardcode.
		float near = 36.0f;
		float far = 500.0f;
		float to_return = far / (far - near) * (1.0f - near/old_z);
		//std::cout << "Initial z: " << old_z << std::endl;
		
		//if (to_return > 1.0f) std::cout << "Calculated z: " << to_return << std::endl;
		return(to_return);
	}
};

struct TriangleRasterizer
{
	void Rasterize(const Triangle& to_draw)
	{
		//std::cout << "Entered rasterizer." << std::endl;
		//std::cout << "to_draw z: " << to_draw.p0.z << ' ' << to_draw.p1.z << ' ' << to_draw.p2.z << std::endl;
		TextureMode mode = VERTEX;
		std::vector<unsigned char> texture;
		int tex_height = 0;
		int tex_width = 0;
		int bpp = 0;

		Triangle arranged;
    
		bool mid_left = ArrangeTriangle(arranged, to_draw);

		Vector4 top;
		Vector4 mid;
		Vector4 low;

		top.x = arranged.p0.x;
		top.y = arranged.p0.y;
		top.z = arranged.p0.z;

		mid.x = arranged.p1.x;
		mid.y = arranged.p1.y;
		mid.z = arranged.p1.z;

		low.x = arranged.p2.x;
		low.y = arranged.p2.y;
		low.z = arranged.p2.z;

		HalfTriangleRasterizer current_tri;

		current_tri.texture = texture;
		current_tri.tex_height = tex_height;
		current_tri.tex_width = tex_width;
		current_tri.bpp = bpp;
		current_tri.mode = mode;

		current_tri.c0 = arranged.c0;
		current_tri.c1 = arranged.c1;
		current_tri.c2 = arranged.c2;

		current_tri.uv0 = arranged.t0;
		current_tri.uv1 = arranged.t1;
		current_tri.uv2 = arranged.t2;

		current_tri.current_y = std::ceil(top.y);
		current_tri.x_left = current_tri.x_right = top.x;

		current_tri.color_left = current_tri.color_right = current_tri.c0;

		current_tri.uv_left = current_tri.uv_right = current_tri.uv0;

		current_tri.z_left = top.z;
		current_tri.z_right = top.z;

		//std::cout << "Z values: " << top.z << ' ' << mid.z << ' ' << low.z << std::endl;

		if (mid_left)
		{
			current_tri.slope_left = safe_divide(mid.x - top.x, mid.y - top.y);
			current_tri.slope_right = safe_divide(low.x - top.x, low.y - top.y);

			current_tri.dc_left.r = static_cast<float>(current_tri.c1.r - current_tri.c0.r) / (mid.y - top.y);
			current_tri.dc_left.g = static_cast<float>(current_tri.c1.g - current_tri.c0.g) / (mid.y - top.y);
			current_tri.dc_left.b = static_cast<float>(current_tri.c1.b - current_tri.c0.b) / (mid.y - top.y);

			current_tri.dc_right.r = static_cast<float>(current_tri.c2.r - current_tri.c0.r) / (low.y - top.y);
			current_tri.dc_right.g = static_cast<float>(current_tri.c2.g - current_tri.c0.g) / (low.y - top.y);
			current_tri.dc_right.b = static_cast<float>(current_tri.c2.b - current_tri.c0.b) / (low.y - top.y);

			current_tri.duv_left =  1.0f / (current_tri.uv1 + (current_tri.uv0 * -1) * (mid.y - top.y));
			current_tri.duv_right = 1.0f / (current_tri.uv2 + (current_tri.uv0 * -1) * (low.y - top.y));

			current_tri.dz_left = safe_divide(mid.z - top.z, mid.y - top.y);
			current_tri.dz_right = safe_divide(low.z - top.z, low.y - top.y);
		}
		else
		{
			current_tri.slope_left = safe_divide(low.x - top.x, low.y - top.y);
			current_tri.slope_right = safe_divide(mid.x - top.x, mid.y - top.y);

			current_tri.dc_right.r = static_cast<float>(current_tri.c1.r - current_tri.c0.r) / (mid.y - top.y);
			current_tri.dc_right.g = static_cast<float>(current_tri.c1.g - current_tri.c0.g) / (mid.y - top.y);
			current_tri.dc_right.b = static_cast<float>(current_tri.c1.b - current_tri.c0.b) / (mid.y - top.y);

			current_tri.dc_left.r = static_cast<float>(current_tri.c2.r - current_tri.c0.r) / (low.y - top.y);
			current_tri.dc_left.g = static_cast<float>(current_tri.c2.g - current_tri.c0.g) / (low.y - top.y);
			current_tri.dc_left.b = static_cast<float>(current_tri.c2.b - current_tri.c0.b) / (low.y - top.y);

			current_tri.duv_left = 1.0f / (low.y - top.y) *  (current_tri.uv2 + (-1 * current_tri.uv0));
			current_tri.duv_right = 1.0f / (mid.y - top.y) * (current_tri.uv1 + (-1 * current_tri.uv0));

			current_tri.dz_left = safe_divide(low.z - top.z, low.y - top.y);
			current_tri.dz_right = safe_divide(mid.z - top.z, mid.y - top.y);
		}

		current_tri.x_left += current_tri.slope_left * (current_tri.current_y - top.y);
		current_tri.x_right += current_tri.slope_right * (current_tri.current_y - top.y);

		//std::cout << "Rasterizing upper segment." << current_tri.current_y << '/' << mid.y << std::endl;
		current_tri.rasterize(mid.y); // Rasterize upper portion.

		if (mid_left)
		{
			current_tri.slope_left = safe_divide(low.x - mid.x, low.y - mid.y);
			current_tri.dc_left.r = static_cast<float>(current_tri.c2.r - current_tri.c1.r) / (low.y - mid.y);
			current_tri.dc_left.g = static_cast<float>(current_tri.c2.g - current_tri.c1.g) / (low.y - mid.y);
			current_tri.dc_left.b = static_cast<float>(current_tri.c2.b - current_tri.c1.b) / (low.y - mid.y);

			current_tri.duv_left = 1.0f / (low.y - mid.y) * (current_tri.uv2 + -1 * current_tri.uv1);
			current_tri.x_left = mid.x;

			current_tri.z_left = mid.z;
			current_tri.dz_left = safe_divide(low.z - mid.z, low.y - mid.y);
			//current_tri.dz_right = (mid.z - top.z) / (mid.y - top.y);
		}
		else
		{
			current_tri.slope_right = safe_divide(low.x - mid.x, low.y - mid.y);
			current_tri.dc_right.r = static_cast<float>(current_tri.c2.r - current_tri.c1.r) / (low.y - mid.y);
			current_tri.dc_right.g = static_cast<float>(current_tri.c2.g - current_tri.c1.g) / (low.y - mid.y);
			current_tri.dc_right.b = static_cast<float>(current_tri.c2.b - current_tri.c1.b) / (low.y - mid.y);

			current_tri.duv_right = 1.0f / (low.y - mid.y) * (current_tri.uv2 + -1 * current_tri.uv1);
			current_tri.x_right = mid.x;

			current_tri.z_right = mid.z;
			//current_tri.dz_left = (low.z - top.z) / (low.y - top.y);
			current_tri.dz_right = safe_divide(low.z - mid.z, low.y - mid.y);
		}

		current_tri.rasterize(low.y); // Rasterize lower portion.
		//std::cout << "Rasterizing lower segment." << std::endl;
	}
};

struct OrthoProjectionPolicy
{
	Matrix4 GetProjectionMatrix() const
	{
		Matrix4 to_return;
		to_return.Zero();
#if 1
		float left = -160.0f;
		float right = 160.0f;
		float top = 120.0f;
		float bottom = -120.0f;
		float near = 36.0f;
		float far = 500.0f;
		float focus = 25.0f;

		to_return.m[0][0] = 2.0f / (right - left);
		to_return.m[1][1] = 2.0f / (top - bottom);
		to_return.m[2][2] = -2.0f / (far - near);
		to_return.m[3][3] = 1.0f;

		to_return.m[0][3] = -(right + left)/(right - left);
		to_return.m[1][3] = -(top + bottom)/(top - bottom);
		to_return.m[2][3] = -(far + near) / (far - near);
#else
		to_return.m[0][0] = 24.0f;
		to_return.m[1][1] = 24.0f;
		to_return.m[3][3] = 1.0f;
#endif

		return(to_return);
	}
};

void RenderWorld::think()
{
    while(!myDrawList.empty())
    {
        if (myWireframeMode)
        {
			RenderPipeline
				<
					StandardViewportPolicy,
					OrthoProjectionPolicy,
					StandardCameraPolicy,
					DepthTester,
					WireframeTriangleRasterizer
				> pipeline;

            pipeline(myDrawList.front());
        }
        else
        {
			std::vector<unsigned char> empty_texture;
			RenderPipeline
				<
					StandardViewportPolicy,
					StandardProjectionPolicy,
					StandardCameraPolicy,
					DepthTester,
					TriangleRasterizer
				> pipeline;

			pipeline(myDrawList.front());
            //RenderTriangle(myDrawList.front(), empty_texture, 0, 0, 0);
        }

        myDrawList.pop_front();
    }
}

void RenderWorld::setWireframeMode(bool mode)
{
    myWireframeMode = mode;
}

