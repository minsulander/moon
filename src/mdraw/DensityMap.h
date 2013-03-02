#ifndef MDRAW_DENSITYMAP_H
#define MDRAW_DENSITYMAP_H

#include "Export.h"
#include <osg/Image>
#include <osg/BoundingBox>
#include <osg/Shape>
#include <vector>

namespace mdraw {

	/// \brief A density map using osg functions for image processing
	/// \ingroup draw
	class MDRAW_EXPORT DensityMap : public osg::Object {
	public:
		
		enum Channel { CH_R = 0, CH_G, CH_B, CH_A };
		
		DensityMap(osg::Image *image = NULL);
		DensityMap(const DensityMap& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(mdraw, DensityMap);
		
		osg::Image *getImage() { return image.get(); }
		const osg::Image *getImage() const { return image.get(); }
		void setImage(osg::Image *newimage) { image = newimage; }
		
		/// Set coordinate bounds that the image covers
		void setBounds(const float xmin, const float xmax, const float ymin, const float ymax);
		/// Get coordinate bounds
		void getBounds(float& xmin, float& xmax, float& ymin, float& ymax) const;
		void setBounds(const osg::BoundingBox& newbbox) { bbox = newbbox; }
		const osg::BoundingBox& getBounds() const { return bbox; }
		
		/// Set node density - equal to the maximum number of objects placed for an entirely "white" image
		void setDensity(const float value);
		void setDensity(const float value, const Channel channel) { density[channel] = value; }
		/// Get node density
		float getDensity(const Channel channel) const { return density[channel]; }
		
		float getPixelDensity(const unsigned int s, const unsigned int t, const Channel channel = CH_R) const;
		
		unsigned int getNumPositions(const Channel channel = CH_R) const { return positions[channel].size(); }
		osg::Vec3 getPosition(const unsigned int index, const Channel channel = CH_R) const { return positions[channel][index]; }
		unsigned int getNumNormals(const Channel channel = CH_R) const { return normals[channel].size(); }
		osg::Vec3 getNormal(const unsigned int index, const Channel channel = CH_R) const { return normals[channel][index]; }
		
		/// Generate positions for nodes to be created
		virtual void generate(const Channel channel);
		/// Generate positions for all channels
		void generate();

		/// Adjust z-component of positions to the heights of the specified terrain node
		virtual void setHeights(const Channel channel, osg::Node *terrainNode, const bool align = false);
		/// Adjust heights for all channels
		void setHeights(osg::Node *terrainNode, const bool align = false);

		/// Adjust z-component of positions to the heights of the specified heightfield
		virtual void setHeights(const Channel channel, osg::HeightField *hf, const bool align = false);
		/// Adjust heights for all channels
		void setHeights(osg::HeightField *hf, const bool align = false);
		
		/// Create nodes transformed corresponding to generated positions 
		virtual osg::Node* createNode(const Channel channel, osg::Node *node);
		
	protected:
		virtual void generatePixel(const Channel channel, const osg::Vec3& center, const osg::Vec3& range, const float dens);
		bool getIntersection(const osg::Vec3& start, const osg::Vec3& end, osg::Node *node, osg::Vec3& pos, osg::Vec3& normal);
	private:
		osg::ref_ptr<osg::Image> image;
		osg::BoundingBox bbox;
		float density[4];
		std::vector<osg::Vec3> positions[4], normals[4];
	};
}

#endif
