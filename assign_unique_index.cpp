
#include "assign_unique_index.hpp"

#include "is_match.hpp"
#include "scenes.hpp"

#include <iostream>

namespace cur = sam::binary_data;

void cur::assign_unique_index(cur::Scenes & scenes)
{
	auto id = uint32_t{ 0 };

	for (auto & s : scenes.scenes)
	{
		for (auto & t : s.textures)
		{
			if (t.id == 0)
			{
				auto found = false;
				for (auto & otherS : scenes.scenes)
				{
					for (auto & otherT : otherS.textures)
					{
						if (&t != &otherT && is_match(t.hash, otherT.hash))
						{
							found = true;
							if (otherT.id == 0)
							{
								++id;
								t.id = id;
								otherT.id = id;
							}
							else
							{
								t.id = otherT.id;
							}
							break;
						}

						if (found)
						{
							break;
						}
					}
					if (found)
					{
						break;
					}

					for (auto & otherSprite : otherS.sprites)
					{
						for (auto & otherAnimation : otherSprite.animations)
						{
							for (auto & otherT : otherAnimation.textures)
							{
								if (&t != &otherT && is_match(t.hash, otherT.hash))
								{
									found = true;
									if (otherT.id == 0)
									{
										++id;
										t.id = id;
										otherT.id = id;
									}
									else
									{
										t.id = otherT.id;
									}
									break;
								}
							}
							if (found)
							{
								break;
							}
						}
						if (found)
						{
							break;
						}
					}
					if (found)
					{
						break;
					}
				}
				if (!found)
				{
					++id;
					t.id = id;
				}
			}
		}

		for (auto & sprite : s.sprites)
		{
			for (auto & animation : sprite.animations)
			{
				for (auto & t : animation.textures)
				{
					auto found = false;
					for (auto & otherS : scenes.scenes)
					{
						for (auto & otherT : otherS.textures)
						{
							if (&t != &otherT && is_match(t.hash, otherT.hash))
							{
								found = true;
								if (otherT.id == 0)
								{
									++id;
									t.id = id;
									otherT.id = id;
								}
								else
								{
									t.id = otherT.id;
								}
								break;
							}
						}

						if (found)
						{
							break;
						}

						for (auto & otherSprite : otherS.sprites)
						{
							for (auto & otherAnimation : otherSprite.animations)
							{
								for (auto & otherT : otherAnimation.textures)
								{
									if (&t != &otherT && is_match(t.hash, otherT.hash))
									{
										found = true;
										if (otherT.id == 0)
										{
											++id;
											t.id = id;
											otherT.id = id;
										}
										else
										{
											t.id = otherT.id;
										}
										break;
									}
								}
								if (found)
								{
									break;
								}
							}
							if (found)
							{
								break;
							}
						}
					}
					if (!found)
					{
						++id;
						t.id = id;
					}
				}
			}
		}

		for (auto & t : s.bgm)
		{
			if (t.id == 0)
			{
				auto found = false;
				for (auto & otherS : scenes.scenes)
				{
					for (auto & otherT : otherS.bgm)
					{
						if (&t != &otherT && is_match(t.hash, otherT.hash))
						{
							found = true;
							if (otherT.id == 0)
							{
								++id;
								t.id = id;
								otherT.id = id;
							}
							else
							{
								t.id = otherT.id;
							}
							break;
						}

						if (found)
						{
							break;
						}
					}
					if (found)
					{
						break;
					}
				}
				if (!found) {
					++id;
					t.id = id;
				}
			}
		}

		for (auto & t : s.sfx)
		{
			if (t.id == 0)
			{
				auto found = false;
				for (auto & otherS : scenes.scenes)
				{
					for (auto & otherT : otherS.sfx)
					{
						if (&t != &otherT && is_match(t.hash, otherT.hash))
						{
							found = true;
							if (otherT.id == 0)
							{
								++id;
								t.id = id;
								otherT.id = id;
							}
							else
							{
								t.id = otherT.id;
							}
							break;
						}

						if (found)
						{
							break;
						}
					}
					if (found)
					{
						break;
					}
				}
				if (!found)
				{
					++id;
					t.id = id;
				}
			}
		}
	}

	std::cout << "Assigned " << id << " ids to textures in " << scenes.scenes.size() << " scenes" << std::endl;
}
